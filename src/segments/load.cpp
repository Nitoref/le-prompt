#ifdef _WIN32
#	include <windows.h>
#else
#	include "unistd.h"
#	include "sys/types.h"
#	include "sys/resource.h"
#endif

#include "utils.hpp"
#include "modules.hpp"



Module SegmentLoad(const config& c)
{
	double load[3];
	getloadavg(load, 3);
	
	std::string output = c.load.symbol;
	output += std::to_string(load[0]).substr(0, 4); 
	output += ' ';
	output += std::to_string(load[1]).substr(0, 4); 
	output += ' ';
	output += std::to_string(load[2]).substr(0, 4); 
    
    return Module {
    	{
    		segment::id::aws,
			output,
			c.load.theme
    	}
    };
}
