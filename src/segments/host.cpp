#include <string>
#ifdef _WIN32
# include <Windows.h>
#else
# include <unistd.h>
#endif

#include "modules.hpp"



Module
SegmentHost(const config& c)
{
    char* hostname = (char*)malloc(256);
    gethostname(hostname, 256);
    
    if (!hostname)
    {
    	return {};
    }

    std::string content = hostname;
    if (c.host.shorten)
    {
	    if (size_t dot  = content.find('.');
	    	       dot != std::string::npos)
	    {
	    	content.erase(dot);
	    }
    }

	return Module {
		{
			segment::id::home,
			content,
			c.host.theme
		}
	};
}
