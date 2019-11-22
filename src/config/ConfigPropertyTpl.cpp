#include "ConfigItem.h"
#include "../UseRegex.h"
#include <iostream>
using namespace SeaDrip::Binaland;

ConfigPropertyTpl::ConfigPropertyTpl( std::string tpl ) : m_b_well_loaded( false )
{
    //  +f, , class std::string, m_s_input_file, InputFileName, defaultValue
    std::cout << "???" << tpl << std::endl;
    auto ret = SeaDrip::regex_all( "\\+([^,]*)\\,([^\\,]*)\\,([^\\,]+)\\,([^\\,]+)\\,([^\\,]+)\\,([^\\,]*)", tpl );
    if( ret.size() < 6 )
    {
        return;
    }
    this->m_s_shell_flag = ret[ 1 ];
    this->m_s_config_file_item = ret[ 2 ];
    this->m_s_property_type = ret[ 3 ];
    this->m_s_property_name = ret[ 4 ];
    this->m_s_method_name = ret[ 5 ];
    this->m_s_default_value = ret[ 6 ];
    this->m_b_well_loaded = true;
    std::cout << this->m_s_method_name << std::endl;
}

bool ConfigPropertyTpl::IsValid( void ) const noexcept
{
    return !( !this->m_b_well_loaded
        || this->m_s_property_type.empty()
        || this->m_s_property_name.empty()
        || this->m_s_method_name.empty()
        || false );
}

bool ConfigPropertyTpl::IsBoolProperty( void ) const noexcept
{
    return this->m_s_property_type == "bool";
}

bool ConfigPropertyTpl::CanBeSetByConfigFile( void ) const noexcept
{
    return !this->m_s_config_file_item.empty();
}

bool ConfigPropertyTpl::CanBeSetByShell( void ) const noexcept
{
    return !this->m_s_shell_flag.empty();
}

std::string ConfigPropertyTpl::GetDeclears( int tabs ) const noexcept
{
    return TabSpace( tabs ) + "// Declear " + this->m_s_property_name + "\n" + TabSpace( tabs )
        +"public:\n" + this->GetMethodDeclear( tabs + 1 ) + "\n" + TabSpace( tabs ) + "protected:\n" + this->GetPropertyDeclear( tabs + 1 );
}

std::string ConfigPropertyTpl::GetMethodDeclear( int tabs ) const noexcept
{
    std::string ret = TabSpace( tabs ) + this->m_s_property_type + ( this->IsBoolProperty() ? " Is" : " Get" )
        + this->m_s_method_name + "( void ) const noexcept;\n" + TabSpace( tabs ) + "void Set"
        + this->m_s_method_name + "( " + this->m_s_property_type + " );";
    return ret;
}

std::string ConfigPropertyTpl::GetPropertyDeclear( int tabs ) const noexcept
{
    std::string ret = TabSpace( tabs ) + "TConfigProperty<" + this->m_s_property_type + "> " + this->m_s_property_name + ";";
    return ret;
}
