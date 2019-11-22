#include "ConfigItem.h"
#include <fstream>
#include "../UseRegex.h"

using namespace SeaDrip::Binaland;

std::string TrimStr( std::string str )
{
    return str;
}

std::string GetConfigName( std::string str )
{
    return SeaDrip::regex( "name\\s*=\\s*(.+)", str, 1 );
}

ConfigItem::ConfigItem( std::string in, std::string codepath ) : m_s_tpl( in ), m_s_target_path( codepath ), m_b_tpl_parsed( false ),
    m_s_out_cpp_path( "" ), m_s_out_header_path( "" )
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
        std::string sline = TrimStr( line );
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
            this->m_s_config_name = GetConfigName( sline );
        }
    }
    return 0;
}

int ConfigItem::SaveOutput()
{
    return 0;
}
