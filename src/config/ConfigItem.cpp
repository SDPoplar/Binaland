#include "ConfigItem.h"
#include <fstream>
#include "../UseRegex.h"
#include <boost/algorithm/string/split.hpp>

using namespace SeaDrip::Binaland;

bool MatchItem( std::string str, std::string& itemName, std::string& value )
{
    auto find = SeaDrip::regex_all( "([^=]+)=(.+)", str );
    if( find.size() != 3 )
    {
        return false;
    }

    itemName = find[ 1 ];
    value = find[ 2 ];
    return true;
}

ConfigItem::ConfigItem( std::string in, std::string codepath, std::string useNamespace ) : m_s_tpl( in ), m_s_target_path( codepath ),
    m_s_namespace( useNamespace ), m_b_tpl_parsed( false ), m_s_out_cpp_path( "" ), m_s_out_header_path( "" )
{}

int ConfigItem::Build()
{
    int ret = this->ParseTpl();
    return ret ? ret : this->SaveOutput();
}

int ConfigItem::ParseTpl()
{
    std::fstream in( this->m_s_tpl, std::ios::in );
    if( !in )
    {
        return 1;
    }
    char line[ 128 ] = "";
    while( !in.eof() )
    {
        in.getline( line, 128 );
        std::string sline = TrimStr( std::string( line ) );
        if( sline.empty() || ( sline.c_str()[ 0 ] == '#' ) )
        {
            continue;
        }
        if( sline.c_str()[ 0 ] == '+' )
        {
            ConfigPropertyTpl prop( sline );
            if( boost::starts_with( prop.GetPropertyType(), "class " )
                && ( std::find( this->m_arr_unknown_classes.begin(), this->m_arr_unknown_classes.end(), prop.GetPropertyType() ) == this->m_arr_unknown_classes.end() ) )
            {
                this->m_arr_unknown_classes.push_back( prop.GetPropertyType() );
            }
            this->m_arr_property_tpls.push_back( prop );
            continue;
        }
        std::string key, val;
        if( !MatchItem( sline, key, val ) )
        {
            continue;
        }
        if( this->m_s_config_name.empty() && ( key == "name" ) )
        {
            this->m_s_config_name = val;
            continue;
        }
        if( this->m_arr_includes.empty() && ( key == "include" ) )
        {
            this->m_arr_includes = SplitStr( ",", val );
        }
    }
    this->m_s_out_header_path = this->m_s_target_path + "/" + this->m_s_config_name + ".h";
    this->m_s_out_cpp_path = this->m_s_target_path + "/" + this->m_s_config_name + ".cpp";
    return 0;
}

int ConfigItem::SaveOutput()
{
    std::ofstream header( this->m_s_out_header_path, std::ios::out ), cpp( this->m_s_out_cpp_path, std::ios::out );
    if( !header || !cpp )
    {
        CLOSE_OPENED_FILE( header );
        CLOSE_OPENED_FILE( cpp );
        return 2;
    }

    std::string header_once_macro = "__SD_" + boost::to_upper_copy( this->m_s_namespace ) + "_" + boost::to_upper_copy( this->m_s_config_name ) + "_H__";
    header << "#ifndef " << header_once_macro << "\n#define " << header_once_macro;
    for( auto item : this->m_arr_includes )
    {
        header << "\n#include " << item;
    }
    header << "\n#include <seadrip/ConfigProperty.hpp>\nnamespace SeaDrip\n{\n"
        << TabSpace( 1 ) << "namespace " << this->m_s_namespace << "\n" << TabSpace( 1 ) << "{\n" << TabSpace( 2 ) << "class " << this->m_s_config_name
        << "\n" << TabSpace( 2 ) << "{\n" << TabSpace( 2 ) << "public:\n" << TabSpace( 3 ) << this->m_s_config_name << "( int, char** );\n";

    cpp << "#include \"" << this->m_s_config_name << ".h\"\n#include <unistd.h>\n";
    for( auto item : this->m_arr_unknown_classes )
    {
        cpp << "// include header file for " << item << "\n";
    }
    cpp << "using namespace SeaDrip::" << this->m_s_namespace << ";\n\n";

    std::string defval = "";
    std::string options = "";
    std::string optioncases = "";
    for( auto item : this->m_arr_property_tpls )
    {
        header << item.GetDeclears( 2 ) << "\n";
        cpp << item.GetMethodCode( this->m_s_config_name ) << "\n";
        if( item.HasDefVal() )
        {
            if( !defval.empty() )
            {
                defval += ", ";
            }
            defval += item.GetDefValInit();
        }
        if( item.CanBeSetByShell() )
        {
            options += item.GetShellOption();
            optioncases += ( TabSpace( 3 ) + item.GetShellOverrideCase() );
        }
    }

    header << TabSpace( 2 ) << "};\n" << TabSpace( 1 ) << "};\n};\n#endif";
    cpp << this->m_s_config_name + "::" + this->m_s_config_name + "( int argc, char** argv )" << ( defval.empty() ? "" : " : " ) << defval << "\n{\n"
        << TabSpace( 1 ) << "char ch;\n" << TabSpace( 1 ) << "while( ( ch = getopt( argc, argv, \"" << options <<"\" ) ) != -1 )\n" << TabSpace( 1 )
        << "{\n" << TabSpace( 2 ) << "switch( ch )\n" << TabSpace( 2 ) << "{\n" << optioncases << TabSpace( 2 ) << "}\n" << TabSpace( 1 ) << "}\n}\n";

    header.close();
    cpp.close();
    return 0;
}
