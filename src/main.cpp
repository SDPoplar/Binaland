#include "config/ConfigItem.h"

#include <iostream>

void ShowUsage()
{
    std::cout << "Usage: binaland use_namespace input_ini [target_path]" << std::endl;
    std::cout << "    target_path: 'src/config' will be used if not given" << std::endl;
}

int main( int argc, char** argv )
{
    if( argc < 3 )
    {
        ShowUsage();
        return 1;
    }
    SeaDrip::Binaland::ConfigItem binaland( argv[ 2 ], argc > 3 ? argv[ 3 ] : "src/config", argv[ 1 ] );
    return binaland.Build();
}
