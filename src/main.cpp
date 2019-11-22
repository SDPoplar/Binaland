#include "config/ConfigItem.h"

int main( int argc, char** argv )
{
    SeaDrip::Binaland::ConfigItem test( "tpl/def.config.ini", "src/config", "Binaland" );
    return test.Build();
}

