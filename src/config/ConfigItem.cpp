#include "ConfigItem.h"
#include <fstream>
#include <boost/regex.hpp>
#include <boost/algorithm/string/split.hpp>
#include <seadrip/KvFileReader.hpp>
#include <seadrip/template.hpp>
#include <seadrip/tpl/config.h>

using namespace SeaDrip::Binaland;

bool MatchItem( std::string str, std::string& itemName, std::string& value )
{
    boost::regex pattern( "([^=]+)=(.+)" );
    boost::smatch find;
    if( !boost::regex_search( str, find, pattern ) || ( find.size() != 3 ) )
    {
        return false;
    }

    std::string n = find[ 1 ];
    itemName = boost::trim_copy( n );
    std::string v = find[ 2 ];
    value = boost::trim_copy( v );
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
        std::string sline = line;
        sline = boost::trim_copy( sline );
        if( sline.empty() || ( sline.c_str()[ 0 ] == '#' ) )
        {
            continue;
        }
        if( sline.c_str()[ 0 ] == '+' )
        {
            ConfigPropertyTpl prop( line + 1 );
            if( !prop.IsValid() )
            {
                continue;
            }
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
            boost::split( this->m_arr_includes, val, boost::is_any_of( "," ), boost::token_compress_on );
            continue;
        }
        if( this->m_s_def_cfgfile.empty() && (key == "def-file") )
        {
            this->m_s_def_cfgfile = val;
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

    std::string header_content = sdtpl_config_header, declear_indent = SeaDrip::Template::GetFrontSpace( header_content, "__REPFLAG_DELCEAR_METHODS__" );
    boost::replace_all( header_content, "__REPFLAG_REQUIRE_LOCK__",
        boost::to_upper_copy( this->m_s_namespace ) + "_" + boost::to_upper_copy( this->m_s_config_name ) );
    boost::replace_all( header_content, "__REPFLAG_NAME_SPACE__", this->m_s_namespace );
    boost::replace_all( header_content, "__REPFLAG_CLASS_NAME__", this->m_s_config_name );

    std::string code_content = sdtpl_config_code;
    boost::replace_all( code_content, "__REPFLAG_CLASS_NAME__", this->m_s_config_name );
    boost::replace_all( code_content, "__REPFLAG_NAME_SPACE__", this->m_s_namespace );

    std::string defval = "";
    std::string options = "";
    std::string optioncases = "";
    std::string headerdeclears = "";
    std::string methodcodes = "";
    std::string boolmap = "";
    for( auto item : this->m_arr_property_tpls )
    {
        headerdeclears += ( SeaDrip::Template::FillIndent( item.GetDeclears(), declear_indent ) + "\n" );
        methodcodes += ( item.GetMethodCode( this->m_s_config_name ) + "\n" );
        if( item.HasDefVal() )
        {
            defval += ( ", " + item.GetDefValInit() );
        }
        if( item.CanBeSetByShell() )
        {
            options += item.GetShellOption();
            optioncases += ( "    " + item.GetShellOverrideCase() );
        }
        if( item.IsBoolProperty() )
        {
            boolmap += ( item.GetBoolShellSetter() + "\n" );
        }
    }
    boost::replace_first( header_content, "__REPFLAG_DELCEAR_METHODS__", headerdeclears );
    boost::replace_first( code_content, "__REPFLAG_METHOD_CODE__", methodcodes );
    boost::replace_first( code_content, "__REPFLAG_DEF_VAL__", defval );
    boost::replace_first( code_content, "__REPFLAG_SHELL_OPTIONS__", options );
    boost::replace_first( code_content, "__REPFLAG_BOOL_PROP_MAP__", boolmap );

    header << header_content;
    header.close();
    cpp << code_content;
    cpp.close();
    return 0;
}
