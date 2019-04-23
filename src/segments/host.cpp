#include <cstring>
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
    char* content_cstr = (char*)malloc(256);
    gethostname(content_cstr, 256);
    
    if (!content_cstr)
    {
    	return {};
    }

    auto content = c.host.symbol;
    content += content_cstr;

    if (c.host.shorten)
    {
	    if (size_t dot  = content.find('.');
	    	       dot != std::string::npos)
	    {
	    	content = content.substr(dot);
	    }
    }

	return Module {
		{
			segment::id::host,
			content,
			c.host.theme
		}
	};
}
