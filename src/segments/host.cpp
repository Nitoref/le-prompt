#define HOSTNAME_MAX 256

#include <string>
#include <cstdlib>
#include <unistd.h>
#include "../segments.hpp"



MultiSegment
SegmentHost(PromptConfig p)
{
	Segment segment;

    char* hostname = (char*)malloc(HOSTNAME_MAX);
    gethostname(hostname, HOSTNAME_MAX);

    if (hostname == p.args.default_host) {
    	return {segment};
    }
    segment.content = hostname;
    segment.content.erase(segment.content.find('.'));
    segment.style = p.theme.hostname;
	
	return {segment};
};
