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
        };

        class ConfigItem
        {
            public:
                ConfigItem( std::string tpl, std::string codepath );
                ~ConfigItem() {}

                std::string GetTplPath() const noexcept;
                int Build();
            protected:
                int ParseTpl();
                int SaveOutput();

                std::vector<ConfigPropertyTpl> m_arr_property_tpls;
                std::string m_s_config_name;
            private:
                bool m_b_tpl_parsed;
                std::string m_s_tpl;
                std::string m_s_target_path;
                std::string m_s_out_header_path;
                std::string m_s_out_cpp_path;
        };
    };
};

#endif

