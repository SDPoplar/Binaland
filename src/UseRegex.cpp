#include "UseRegex.h"

#if defined( _WIN32 ) or defined( _WIN64 )
#include <regex>
#define REGEX_NS std
#else
#include <boost/regex.hpp>
#define REGEX_NS boost
#endif

std::string SeaDrip::regex( std::string pattern, std::string search )
{
    REGEX_NS::regex _pattern( pattern );
    return REGEX_NS::regex_match( search, _pattern ) ? search : "";
}

std::string SeaDrip::regex( std::string pattern, std::string search, int retIndex )
{
    REGEX_NS::regex _pattern( pattern );
    REGEX_NS::smatch matches;
    return ( REGEX_NS::regex_search( search, matches, _pattern ) && ( matches.size() > retIndex ) ) ? std::string( matches[ retIndex ] ) : "";
}

std::vector<std::string> SeaDrip::regex_all( std::string pattern, std::string search )
{
    std::vector<std::string> ret;
    REGEX_NS::regex _pattern( pattern );
    REGEX_NS::smatch matches;
    if( REGEX_NS::regex_search( search, matches, _pattern ) )
    {
        for( std::string item : matches )
        {
            ret.push_back( item );
        }
    }
    return ret;
}
