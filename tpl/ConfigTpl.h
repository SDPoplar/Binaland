#include <seadrip/template.hpp>

TEMPLATE_START( config_header );
#ifndef __SD_TPL_REPLACE_KEEPSPACE( require_lock, BINALAND_BINALANDCONFIG )_H__
#define __SD_TPL_REPLACE_KEEPSPACE( require_lock, BINALAND_BINALANDCONFIG )_H__
#include <string>
#include <seadrip/ConfigProperty.hpp>
namespace SeaDrip
{
    namespace TPL_REPLACE_KEEPSPACE( name_space, Binaland )
    {
        class TPL_REPLACE_KEEPSPACE( class_name, BinalandConfig )
            : public SeaDrip::TPL_REPLACE_KEEPSPACE( config_base_class, BaseConfig )
        {
        public:
            TPL_REPLACE_KEEPSPACE( class_name, BinalandConfig )( std::string def_cfg_path );
        protected:
            void ShellOverride( char shell_flag, std::string val ) override;

        TPL_REPLACE( delcear_methods );
        };
    };
};
#endif
