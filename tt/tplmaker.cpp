#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>

void usage()
{
    std::cout << "usage: sdtpl tpl_file target_file [-a|-o|-g]" << std::endl
        << "  @target_file: path_root = /usr/include/seadrip/tpl/" << std::endl
        << "  @save_mode: what to do if target_file has already exists, -o as default" << std::endl
        << "    -o: override target_file if already exists" << std::endl
        << "    -a: append to file if already exists" << std::endl
        << "    -g: give up save" << std::endl
        ;
}

std::string ReplaceMacro( std::string line )
{
    boost::regex block_pattern( "TPL_REPLACE\\(\\s*([^\\s]+)\\s*\\);" );
    boost::regex space_pattern( "TPL_REPLACE_KEEPSPACE\\(\\s*([^,|^\\s]+),[^\\)]+\\)" );
    std::string ret = boost::regex_replace( line, block_pattern,
        [](boost::match_results<std::string::const_iterator> match)->std::string{
            return ( match.size() <  2 ) ? match[ 0 ] : ( "__REPFLAG_" + boost::to_upper_copy( std::string( match[ 1 ] ) ) + "__" );
        } );
    return boost::regex_replace( ret, space_pattern,
        [](boost::match_results<std::string::const_iterator> match)->std::string{
            return ( match.size() < 2 ) ? match[ 0 ] : ( "__REPFLAG_" + boost::to_upper_copy( std::string( match[ 1 ] ) ) + "__" );
        } );
}

bool GiveupSave( std::string target, int argc, char** argv )
{
    if( ~access( target.c_str(), F_OK ) || ( argc < 4 ) )
    {
        return false;
    }
    return std::string( argv[ 3 ] ) == "-g";
}

bool CheckSave( std::string target )
{
    std::string path = target.substr( 0, target.find_last_of( '/' ) );
    return path.empty() || !access( path.c_str(), F_OK )
        || ( CheckSave( path ) && !mkdir( path.c_str(), S_IREAD | S_IWRITE | S_IRGRP | S_IROTH ) );
}

bool ParseTemplate( std::string tpl_file, std::string& name, std::string& content )
{
    std::ifstream in( tpl_file, std::ios::in );
    std::string sline = "";
    bool started = false;
    boost::regex pattern( "TEMPLATE_START\\(\\s*([^\\s]+)\\s*\\);" );
    while( !in.eof() )
    {
        char line[ 256 ];
        in.getline( line, 256 );
        sline = line;
        if( started )
        {
            sline = ReplaceMacro( sline );
            if( !sline.empty() )
            {
                content += ( sline + "\\n" );
            }
            continue;
        }
        boost::smatch matches;
        if( boost::regex_search( sline, matches, pattern )
            && ( matches.size() > 0 ) )
        {
            started = true;
            name = matches[ 1 ];
        }
    }
    in.close();
    return true;
}

int main( int argc, char**argv )
{
    if( ( argc < 3 ) || ( std::string( argv[ 1 ] ) == "--help" ) )
    {
        usage();
        return 0;
    }

    std::string tplname, content;
    if( !ParseTemplate( argv[ 1 ], tplname, content ) )
    {
        std::cout << "tpl_file not found" << std::endl;
        return 1;
    }

    if( content.empty() )
    {
        std::cout << "No valid content found" << std::endl;
    }
    std::string target = argv[ 2 ];
    if( target.c_str()[ 0 ] != '/' )
    {
        target = "/usr/include/seadrip/tpl/" + target;
    }
    if( GiveupSave( target, argc, argv ) )
    {
        std::cout << "Give up save because file already exists" << std::endl;
        return 0;
    }
    std::cout << "Saving template with name [" << tplname << "]..." << std::endl;
    if( !CheckSave( target ) )
    {
        std::cout << "Cannot save to file " << target << std::endl;
        return 0;
    }
    auto mode = std::ios::out;
    if( ( argc > 3 ) && ( std::string( argv[ 3 ] ) == "-a" ) )
    {
        mode = mode | std::ios::app;
    }
    std::ofstream out( target, mode );
    if( !out )
    {
        std::cout << "Open target file " << target << " failed" << std::endl;
        return 0;
    }

    boost::replace_all( content, "\"", "\\\"" );
    out << "const char* sdtpl_" << tplname << " = \"" << content << "\";\n";
    out.close();
    return 0;
}
