#ifdef _WIN32
#	include <windows.h>
#else
#	include "unistd.h"
#	include "sys/types.h"
#	include "sys/resource.h"
#endif

#include "utils.hpp"
#include "modules.hpp"
#include "printer.hpp"



Segment SegmentLoad(const config& c)
{

#ifdef _WIN32
	return {}
#else
	double load[3];
	getloadavg(load, 3);
	
	Segment segment(segment::id::aws);
	segment.theme(c.load.theme);
	segment.append(c.load.symbol);

	segment.append(std::to_string(load[0]).substr(0, 4));
	segment.append(' ');
	segment.append(std::to_string(load[1]).substr(0, 4));
	segment.append(' ');
	segment.append(std::to_string(load[2]).substr(0, 4));
    
    return segment;
#endif
}
