#ifndef __SD_Binaland_BinalandConfig_H__
#define __SD_Binaland_BinalandConfig_H__
#include <seadrip/ConfigProperty.hpp>
namespace SeaDrip
{
    namespace Binaland
        {
            class BinalandConfig : public SeaDrip::SeaDripConfig
            {
            // Declear m_s_class_name
            public:
                class std::string GetConfigClassName( void ) const noexcept;
                void SetConfigClassName( class std::string );
            protected:
                TConfigProperty<class std::string> m_s_class_name;
            // Declear m_s_code_path
            public:
                class std::string GetCodePath( void ) const noexcept;
                void SetCodePath( class std::string );
            protected:
                TConfigProperty<class std::string> m_s_code_path;
            // Declear m_s_tpl_path
            public:
                class std::string GetTemplatePath( void ) const noexcept;
                void SetTemplatePath( class std::string );
            protected:
                TConfigProperty<class std::string> m_s_tpl_path;
            // Declear m_s_cpp_suffix
            public:
                class std::string GetCodeSuffix( void ) const noexcept;
                void SetCodeSuffix( class std::string );
            protected:
                TConfigProperty<class std::string> m_s_cpp_suffix;
            // Declear m_s_input_file
            public:
                class std::string GetInputFileName( void ) const noexcept;
                void SetInputFileName( class std::string );
            protected:
                TConfigProperty<class std::string> m_s_input_file;
}
        }
    }
#endif