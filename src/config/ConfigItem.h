#ifndef     __SD_BINALAND_CONFIG_CONFIG_ITEM_H__
#define     __SD_BINALAND_CONFIG_CONFIG_ITEM_H__

#include <string>
#include <vector>

namespace SeaDrip
{
    namespace Binaland
    {
        class ConfigPropertyTpl
        {
            public:
                ConfigPropertyTpl( std::string config );
                bool IsValid() const noexcept;
                std::string GetPropertyType( void ) const noexcept;
                bool CanBeSetByShell() const noexcept;
                bool CanBeSetByConfigFile() const noexcept;
                bool IsBoolProperty() const noexcept;
                bool HasDefVal() const noexcept;
                std::string GetDefValInit() const noexcept;
                std::string GetDeclears() const noexcept;
                std::string GetPropertyDeclear() const noexcept;
                std::string GetMethodDeclear() const noexcept;
                std::string GetMethodCode( std::string configName ) const noexcept;
                std::string GetShellOption() const noexcept;
                std::string GetShellOverrideCase() const noexcept;
                std::string GetBoolShellSetter() const noexcept;

            protected:
                std::string m_s_shell_flag;
                std::string m_s_config_file_item;
                std::string m_s_property_type;
                std::string m_s_property_name;
                std::string m_s_method_name;
                std::string m_s_default_value;

                bool m_b_well_loaded;
        };

        class ConfigItem
        {
            public:
                ConfigItem( std::string tpl, std::string codepath, std::string useNamespace );
                ~ConfigItem() {}

                std::string GetTplPath() const noexcept;
                int Build();
            protected:
                int ParseTpl();
                int SaveOutput();

                std::vector<ConfigPropertyTpl> m_arr_property_tpls;
                std::string m_s_config_name;
                std::string m_s_def_cfgfile;
            private:
                bool m_b_tpl_parsed;
                std::string m_s_namespace;
                std::string m_s_tpl;
                std::string m_s_target_path;
                std::string m_s_out_header_path;
                std::string m_s_out_cpp_path;
                std::vector<std::string> m_arr_includes;
                std::vector<std::string> m_arr_unknown_classes;
        };
    };
};

#define CLOSE_OPENED_FILE( var ) do             \
{                                               \
    if( var.is_open() )                         \
    {                                           \
        var.close();                            \
    }                                           \
} while( false )

#endif

