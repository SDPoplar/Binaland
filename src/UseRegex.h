#ifndef __SD_USE_REGEX_H__
#define __SD_USE_REGEX_H__

#include <string>
#include <vector>

namespace SeaDrip
{
    std::string regex( std::string pattern, std::string search );
    std::string regex( std::string pattern, std::string search, int retIndex );
    std::vector<std::string> regex_all( std::string pattern, std::string search );
};

#endif
