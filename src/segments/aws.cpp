#include "utils.hpp"
#include "modules.hpp"
#include <cstdlib>


Module SegmentAws(const config& c)
{
    return Module {
    	{
    		segment::id::aws,
			utils::string(std::getenv("AWS_PROFILE")),
			c.aws.theme
    	}
    };
}
