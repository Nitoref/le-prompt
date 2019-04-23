#include <string>
#ifdef _WIN32
#   include <Windows.h>
#else
#   include <pwd.h>
#   include <unistd.h>
#endif
#include <cstdlib>

#include "modules.hpp"
#include "utils.hpp"



Segment
SegmentUser(const config& c)
{
    
#ifdef _WIN32
    char  content_cstr[UNLEN+1];
    DWORD user_name_size = sizeof(content_cstr);
    if (GetUserName(content_cstr, &user_name_size))
    {
        content_cstr = std::getenv("USERNAME");
    }
#else
    char* content_cstr = std::getenv("USER");
    if (!content_cstr)
    {
        content_cstr = getpwuid(getuid())->pw_name;
    }
#endif

    if (!content_cstr)
    {
        return {};
    }
    if(!c.user.always && content_cstr == c.user.ignore)
    {
    	return {};
    }

    Segment segment(segment::id::user);
    if (c._meta.root)
        segment.theme(c.user.theme_root);
    else
        segment.theme(c.user.theme);
    segment.append(c.user.symbol);
    segment.append(utils::string(content_cstr));
    return segment;
}
