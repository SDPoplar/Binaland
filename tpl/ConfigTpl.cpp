#include <seadrip/template.hpp>
#include "ConfigTpl.h"
TEMPLATE_START( config_code );
#include "TPL_REPLACE_KEEPSPACE( class_name, BinalandConfig ).h"
using namespace SeaDrip::TPL_REPLACE_KEEPSPACE( name_space, BinalandConfig );

TPL_REPLACE_KEEPSPACE( class_name, BinalandConfig )::TPL_REPLACE_KEEPSPACE( class_name, BinalandConfig )( std::string def_cfg_path ) :
    SeaDrip::TPL_REPLACE_KEEPSPACE( config_base_class, BaseConfig )( def_cfg_path )TPL_REPLACE_KEEPSPACE( def_val, /**/ )
{
    this->m_s_shell_options = "c:TPL_REPLACE_KEEPSPACE( shell_options, s )";
    TPL_REPLACE( bool_prop_map );
}

void TPL_REPLACE_KEEPSPACE( class_name, BinalandConfig )::ShellOverride( char shell_flag, std::string val )
{

}

TPL_REPLACE( method_code );
