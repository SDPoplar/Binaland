#include "UseRegex.h"

std::string SeaDrip::regex( std::string pattern, std::string search )
{
    REGEX_NS::regex _pattern( pattern );
    return REGEX_NS::regex_match( search, _pattern ) ? search : "";
}

std::string SeaDrip::regex( std::string pattern, std::string search, int retIndex )
{
    REGEX_NS::regex _pattern( pattern );
    REGEX_NS::smatch matches;
    return ( REGEX_NS::regex_search( search, matches, _pattern ) && ( matches.size() > retIndex ) ) ? TrimStr( std::string( matches[ retIndex ] ) ) : "";
}

std::vector<std::string> SeaDrip::regex_all( std::string pattern, std::string search )
{
    std::vector<std::string> ret;
    REGEX_NS::regex _pattern( pattern );
    REGEX_NS::smatch matches;
    if( REGEX_NS::regex_search( search, matches, _pattern, REGEX_NS::match_extra ) )
    {
        for( std::string item : matches )
        {
            ret.push_back( TrimStr( item ) );
        }
    }
    return ret;
}

std::string SeaDrip::TabSpace( int num )
{
    std::string ret = "";
    for( int i=0; i<num; i++ )
    {
        ret += "    ";
    }
    return ret;
}

std::vector<std::string> SeaDrip::SplitStr( std::string splitBy, std::string str )
{
    std::vector<std::string> ret;
    boost::split( ret, str, boost::is_any_of( splitBy ), boost::token_compress_on );
    for( auto& item : ret )
    {
        item = boost::trim_copy( item );
    }
    return ret;
}
