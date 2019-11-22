#include "ConfigItem.h"
#include <fstream>
#include "../UseRegex.h"

using namespace SeaDrip::Binaland;

std::string GetConfigName( std::string str )
{
    return SeaDrip::regex( "name\\s*=\\s*(.+)", str, 1 );
}

std::vector<std::string> GetIncludes( std::string str )
{
    std::vector<std::string> ret;
    return ret;
    return SeaDrip::regex( "include\\s*=.*", str ).empty() ? SeaDrip::regex_all( ".+", str ) : ret;
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
            this->m_arr_property_tpls.push_back( ConfigPropertyTpl( sline ) );
        }
        if( this->m_s_config_name.empty() )
        {
            std::cout << "name:" << sline << std::endl;
            this->m_s_config_name = GetConfigName( sline );
        }
        /*
        if( this->m_arr_includes.empty() )
        {
            std::cout << "include:" << sline << std::endl;
            this->m_arr_includes = GetIncludes( sline );
        }
        */
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

    std::string header_once_macro = "__SD_" + this->m_s_namespace + "_" + this->m_s_config_name + "_H__";
    header << "#ifndef " << header_once_macro << "\n#define " << header_once_macro;
    for( auto item : this->m_arr_includes )
    {
        header << "#include " << item << "\n";
    }
    header << "\n#include <seadrip/ConfigProperty.hpp>\nnamespace SeaDrip\n{\n"
        << TabSpace( 1 ) << "namespace " << this->m_s_namespace << "\n" << TabSpace( 2 ) << "{\n" << TabSpace( 3 ) << "class " << this->m_s_config_name
        << " : public SeaDrip::SeaDripConfig\n" << TabSpace( 3 ) << "{\n";

    for( auto item : this->m_arr_property_tpls )
    {
        header << item.GetDeclears( 3 ) << "\n";
    }

    header << TabSpace( 3 ) << "}\n" << TabSpace( 2 ) << "}\n" << TabSpace( 1 ) << "}\n#endif";

    header.close();
    cpp.close();
    return 0;
}
