#include "ConfigItem.h"
#include "../UseRegex.h"
#include <iostream>
using namespace SeaDrip::Binaland;

ConfigPropertyTpl::ConfigPropertyTpl( std::string tpl ) : m_b_well_loaded( false )
{
    //  +f, , class std::string, m_s_input_file, InputFileName, defaultValue
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
    if( this->HasDefVal() )
    {
        return;
    }
    if( boost::iends_with( this->m_s_property_type, "string" ) )
    {
        this->m_s_default_value = "\"\"";
        return;
    }
    if( boost::ends_with( this->m_s_property_type, "*" ) )
    {
        this->m_s_default_value = "nullptr";
    }
}

bool ConfigPropertyTpl::IsValid( void ) const noexcept
{
    return !( !this->m_b_well_loaded
        || ( this->m_s_shell_flag == "c" )
        || this->m_s_property_type.empty()
        || this->m_s_property_name.empty()
        || this->m_s_method_name.empty()
        || false );
}

bool ConfigPropertyTpl::IsBoolProperty( void ) const noexcept
{
    return this->m_s_property_type == "bool";
}

std::string ConfigPropertyTpl::GetPropertyType( void ) const noexcept
{
    return this->m_s_property_type;
}

bool ConfigPropertyTpl::CanBeSetByConfigFile( void ) const noexcept
{
    return !this->m_s_config_file_item.empty();
}

bool ConfigPropertyTpl::CanBeSetByShell( void ) const noexcept
{
    return !this->m_s_shell_flag.empty();
}

bool ConfigPropertyTpl::HasDefVal( void ) const noexcept
{
    return !this->m_s_default_value.empty();
}

std::string ConfigPropertyTpl::GetDeclears( void ) const noexcept
{
    return "\n// Declear " + this->m_s_property_name + "\npublic:\n    " + this->GetMethodDeclear() + "\nprotected:\n    " + this->GetPropertyDeclear();
}

std::string ConfigPropertyTpl::GetMethodDeclear() const noexcept
{
    std::string ret = this->m_s_property_type + ( this->IsBoolProperty() ? " Is" : " Get" )
        + this->m_s_method_name + "( void ) const noexcept;\n    void Set"
        + this->m_s_method_name + "( " + this->m_s_property_type + " );";
    return ret;
}

std::string ConfigPropertyTpl::GetPropertyDeclear( void ) const noexcept
{
    std::string ret = "TConfigProperty<" + this->m_s_property_type + "> " + this->m_s_property_name + ";";
    return ret;
}

std::string ConfigPropertyTpl::GetDefValInit( void ) const noexcept
{
    return this->m_s_property_name + "( " + this->m_s_default_value + " )";
}

std::string ConfigPropertyTpl::GetMethodCode( std::string configName ) const noexcept
{
    return "void " + configName + "::Set" + this->m_s_method_name + "( " + this->m_s_property_type + " val )\n{\n    this->"
        + this->m_s_property_name + ".Set( EConfigSetFrom::RUNTIME, val );\n}\n\n" + this->m_s_property_type + " " + configName
        + ( this->IsBoolProperty() ? "::Is" : "::Get" ) + this->m_s_method_name + "( void ) const noexcept\n{\n    return this->"
        + this->m_s_property_name + ".Get();\n}\n";
}

std::string ConfigPropertyTpl::GetShellOption( void ) const noexcept
{
    return this->m_s_shell_flag + ( this->IsBoolProperty() ? "" : ":" );
}

std::string ConfigPropertyTpl::GetShellOverrideCase() const noexcept
{
    return "case '" + this->m_s_shell_flag + "': this->" + this->m_s_property_name + ".Set( EConfigSetFrom::SHELL, "
        + ( this->IsBoolProperty() ? "true" : "optarg" ) + " ); break;\n";
}

std::string ConfigPropertyTpl::GetBoolShellSetter( void ) const noexcept
{
    return "this->m_map_bool_props[ '" + this->m_s_shell_flag + "' ] = &this->" + this->m_s_property_name  + ";";
}
