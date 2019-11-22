#ifndef __SD_USE_REGEX_H__
#define __SD_USE_REGEX_H__

#include <string>
#include <vector>

#if defined( _WIN32 ) or defined( _WIN64 )
#include <regex>
#define REGEX_NS std
#define TrimStr( s ) s
#else
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#define TrimStr( s ) boost::trim_copy( s )
#define REGEX_NS boost
#endif

namespace SeaDrip
{
    std::string regex( std::string pattern, std::string search );
    std::string regex( std::string pattern, std::string search, int retIndex );
    std::vector<std::string> regex_all( std::string pattern, std::string search );

    std::string TabSpace( int num );
    std::vector<std::string> SplitStr( std::string splitBy, std::string str );
};

#endif
