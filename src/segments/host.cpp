#include <cstring>
#include <string>
#ifdef _WIN32
# include <Windows.h>
#else
# include <unistd.h>
#endif

#include "modules.hpp"



Segment
SegmentHost(const config& c)
{
    char* content_cstr = (char*)malloc(256);
    gethostname(content_cstr, 256);
    
    if (!content_cstr) {
    	return {};
    }

    if (c.host.shorten) {
	    if (char* dot  = strchr(content_cstr, '.');
	    	      dot != NULL) {
	    	*dot = '\0';
	    }
    }

    Segment segment(segment::id::host);
    segment.theme(c.host.theme);
    segment.append(c.host.symbol);
    segment.append(content_cstr);
    return segment;
}
