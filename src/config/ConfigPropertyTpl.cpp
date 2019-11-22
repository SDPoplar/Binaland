#include "ConfigItem.h"
#include "../UseRegex.h"
using namespace SeaDrip::Binaland;

ConfigPropertyTpl::ConfigPropertyTpl( std::string tpl )
{
    auto ret = SeaDrip::regex_all( "\\+(\\w{0,1})\\s*\\,([^\\,^\\s]*)\\s*\\,", tpl );
}

bool ConfigPropertyTpl::IsValid( void ) const noexcept
{
    return false;
}
