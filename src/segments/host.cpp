#define HOSTNAME_MAX 256

#include "modules.hpp"

#include <string>
#include <cstdlib>
#include <unistd.h>



Module
SegmentHost(const config& c)
{

    char* hostname = (char*)malloc(HOSTNAME_MAX);
    gethostname(hostname, HOSTNAME_MAX);
    if (!hostname)
    {
    	return Module {};
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
			module::id::home,
			content,
			c.host.theme
		}
	};
}
