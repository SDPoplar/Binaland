#ifndef __SD_BINALAND_BINALANDCONFIG_H__
#define __SD_BINALAND_BINALANDCONFIG_H__
#include <string>
#include <vector>
#include <seadrip/ConfigProperty.hpp>
namespace SeaDrip
{
    namespace Binaland
    {
        class BinalandConfig : public SeaDrip::BaseConfig
        {
        public:
            BinalandConfig();
        protected:
            void ShellOverride( char shell_flag, std::string val ) override;
        
        // Declear m_s_class_name
        public:
            std::string GetConfigClassName( void ) const noexcept;
            void SetConfigClassName( std::string );
        protected:
            TConfigProperty<std::string> m_s_class_name;

        // Declear m_s_code_path
        public:
            std::string GetCodePath( void ) const noexcept;
            void SetCodePath( std::string );
        protected:
            TConfigProperty<std::string> m_s_code_path;

        // Declear m_s_tpl_path
        public:
            std::string GetTemplatePath( void ) const noexcept;
            void SetTemplatePath( std::string );
        protected:
            TConfigProperty<std::string> m_s_tpl_path;

        // Declear m_s_cpp_suffix
        public:
            std::string GetCodeSuffix( void ) const noexcept;
            void SetCodeSuffix( std::string );
        protected:
            TConfigProperty<std::string> m_s_cpp_suffix;

        // Declear m_s_input_file
        public:
            std::string GetInputFileName( void ) const noexcept;
            void SetInputFileName( std::string );
        protected:
            TConfigProperty<std::string> m_s_input_file;

        // Declear m_b_create_new
        public:
            bool IsCreateMode( void ) const noexcept;
            void SetCreateMode( bool );
        protected:
            TConfigProperty<bool> m_b_create_new;

        };
    };
};
#endif
