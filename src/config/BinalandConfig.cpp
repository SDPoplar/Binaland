#include "BinalandConfig.h"
using namespace SeaDrip::Binaland;
BinalandConfig::BinalandConfig() :
    SeaDrip::BaseConfig( "" ), m_s_class_name( "" ), m_s_code_path( "" ), m_s_tpl_path( "" ), m_s_cpp_suffix( "" ), m_s_input_file( "" ), m_b_create_new( false )
{
    this->m_s_shell_options = "c:n:d:t:f:C";
    this->m_map_bool_props[ 'C' ] = &this->m_b_create_new;

}
void BinalandConfig::ShellOverride( char shell_flag, std::string val )
{
}
void BinalandConfig::SetConfigClassName( std::string val )
{
    this->m_s_class_name.Set( EConfigSetFrom::RUNTIME, val );
}

std::string BinalandConfig::GetConfigClassName( void ) const noexcept
{
    return this->m_s_class_name.Get();
}

void BinalandConfig::SetCodePath( std::string val )
{
    this->m_s_code_path.Set( EConfigSetFrom::RUNTIME, val );
}

std::string BinalandConfig::GetCodePath( void ) const noexcept
{
    return this->m_s_code_path.Get();
}

void BinalandConfig::SetTemplatePath( std::string val )
{
    this->m_s_tpl_path.Set( EConfigSetFrom::RUNTIME, val );
}

std::string BinalandConfig::GetTemplatePath( void ) const noexcept
{
    return this->m_s_tpl_path.Get();
}

void BinalandConfig::SetCodeSuffix( std::string val )
{
    this->m_s_cpp_suffix.Set( EConfigSetFrom::RUNTIME, val );
}

std::string BinalandConfig::GetCodeSuffix( void ) const noexcept
{
    return this->m_s_cpp_suffix.Get();
}

void BinalandConfig::SetInputFileName( std::string val )
{
    this->m_s_input_file.Set( EConfigSetFrom::RUNTIME, val );
}

std::string BinalandConfig::GetInputFileName( void ) const noexcept
{
    return this->m_s_input_file.Get();
}

void BinalandConfig::SetCreateMode( bool val )
{
    this->m_b_create_new.Set( EConfigSetFrom::RUNTIME, val );
}

bool BinalandConfig::IsCreateMode( void ) const noexcept
{
    return this->m_b_create_new.Get();
}


