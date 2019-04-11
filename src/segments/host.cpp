#define HOSTNAME_MAX 256

#include <string>
#include <cstdlib>
#include <unistd.h>
#include "../modules.hpp"



Module
SegmentHost(Config c)
{
	Segment segment;

    char* hostname = (char*)malloc(HOSTNAME_MAX);
    gethostname(hostname, HOSTNAME_MAX);

    if (hostname == c.args.default_host)
    {
    	return Module {};
    }
    
    segment.content = hostname;
    segment.content.erase(segment.content.find('.'));
    segment.style = c.theme.hostname;
    segment.id = module::id::host;
	
	return Module {segment};
}
