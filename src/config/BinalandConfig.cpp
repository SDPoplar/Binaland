#include "BinalandConfig.h"
#include <unistd.h>
using namespace SeaDrip::Binaland;

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

BinalandConfig::BinalandConfig( int argc, char** argv ) : m_s_class_name( "" ), m_s_code_path( "" ), m_s_tpl_path( "" ), m_s_cpp_suffix( "" ), m_s_input_file( "" )
{
    char ch;
    while( ( ch = getopt( argc, argv, "n:c:t:s:f:" ) ) != -1 )
    {
        switch( ch )
        {
            case 'n': this->m_s_class_name.Set( EConfigSetFrom::SHELL, optarg ); break;
            case 'c': this->m_s_code_path.Set( EConfigSetFrom::SHELL, optarg ); break;
            case 't': this->m_s_tpl_path.Set( EConfigSetFrom::SHELL, optarg ); break;
            case 's': this->m_s_cpp_suffix.Set( EConfigSetFrom::SHELL, optarg ); break;
            case 'f': this->m_s_input_file.Set( EConfigSetFrom::SHELL, optarg ); break;
        }
    }
}
