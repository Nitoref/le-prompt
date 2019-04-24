#ifdef _WIN32
#   include <windows.h>
#else
#   include <pwd.h>
#   include <unistd.h>
#endif
#include <string>
#include <cstdlib>

#include "modules.hpp"
#include "utils.hpp"



Segment
SegmentContext(const config& c)
{

#ifdef _WIN32
    char user_cstr[UNLEN+1];
    DWORD user_name_size = sizeof(user_cstr);
    if (GetUserName(user_cstr, &user_name_size)) {
        user_cstr = std::getenv("USERNAME");
    }
#else
    char* user_cstr = std::getenv("USER");
    if (!user_cstr) {
        user_cstr = getpwuid(getuid())->pw_name;
    }
#endif
    std::string user = utils::string(user_cstr);
    
    char host_c_str[256];
    gethostname(host_c_str, 256);
    std::string host = utils::string(host_c_str);
    
    if (host.empty() && user.empty()) {
        return {};
    }

    std::string host_short;
    if (auto dot = host.find('.'); dot != std::string::npos ) {
    	host_short = host.substr(0, dot);
    } else {
        host_short = host;
    }
    

    Segment segment(segment::id::context);

    if (c._meta.root) {
        segment.theme(c.context.theme_root);
    }
    else {
        segment.theme(c.context.theme);
    }

    bool escaped = false;
    for (char ch: c.context.format) {
        if (escaped) {
            segment.append(ch);
        	escaped = false;
        	continue;
        }
        switch(ch) {
            case 'u':
                segment.append(user);
            break;
            case 'h':
                segment.append(host_short);
            break;
            case 'H':
                segment.append(host);
                break;
            case '\\':
                escaped = true;
            break;
            default:
                segment.append(ch);
        }
    }
    return segment;
}
