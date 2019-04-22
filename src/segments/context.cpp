#ifdef _WIN32
#   include <windows.h>
#else
#   include <unistd.h>
#endif
#include <string>
#include <cstdlib>

#include "modules.hpp"
#include "utils.hpp"



Module
SegmentContext(const config& c)
{

#ifdef _WIN32
    char user_cstr[UNLEN+1];
    DWORD user_name_size = sizeof(user_cstr);
    if (GetUserName(user_cstr, &user_name_size))
    {
        username_cstr = std::getenv("USERNAME");
    }
    std::string user = utils::string(user_cstr);
#else
    std::string user = utils::string(std::getenv("USER"));
#endif
    
    char host_c_str[256];
    gethostname(host_c_str, 256);
    std::string host = utils::string(host_c_str);
    

    if (host.empty() && user.empty())
    {
        return {};
    }


    std::string host_short;
    if (auto dot = host.find('.'); dot != std::string::npos )
    {
    	host_short = host.substr(0, dot);
    } else host_short = host;
    


    std::string content;
    bool escaped = false;
    for (char ch: c.context.format)
    {
        if (escaped) {
            content += ch;
        	escaped = false;
        	continue;
        }
        switch(ch)
        {
            case 'u':
                content += user;
            break;
            case 'h':
                content += host_short;
            break;
            case 'H':
                content += host;
                break;
            case '\\':
                escaped = true;
            break;
            default:
                content += ch;
        }
    }

    return Module {
    	{
    		segment::id::context,
    		content,
            c._meta.root ? c.context.theme_root
                         : c.context.theme
    	}
    };
}
