#define HOSTNAME_MAX 256

#include "modules.hpp"
#include "utils.hpp"

#include <string>
#include <cstdlib>
#include <unistd.h>



Module
SegmentContext(const config& c)
{
    char* host_c_str = (char*)malloc(HOSTNAME_MAX);
    gethostname(host_c_str, HOSTNAME_MAX);

    
    std::string host = utils::string(host_c_str);
    std::string user = utils::string(std::getenv("USER"));
    

    if (host.empty() && user.empty())
    {
        return Module {};
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
    		module::id::context,
    		content,
            c._meta.root ? c.context.theme_root
                         : c.context.theme
    	}
    };
}
