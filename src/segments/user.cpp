#include <string>
#ifdef _WIN32
# include <Windows.h>
#endif
#include <cstdlib>

#include "modules.hpp"
#include "utils.hpp"



Module
SegmentUser(const config& c)
{
#ifdef _WIN32
    char  username_cstr[UNLEN+1];
    DWORD user_name_size = sizeof(username_cstr);
    if (GetUserName(username_cstr, &user_name_size))
    {
        username_cstr = std::getenv("USERNAME");
    }
    std::string username = utils::string(username_cstr);
#else
    std::string username = utils::string(std::getenv("USER"));
#endif

    if(!c.user.always && username == c.user.default_user)
    {
    	return {};
    }

    return Module {
        {
            segment::id::user,
            username,
            c._meta.root ? c.user.theme_root
                         : c.user.theme
        }
    };
}
