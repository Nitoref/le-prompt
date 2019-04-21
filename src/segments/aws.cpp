#include "utils.hpp"
#include "modules.hpp"
#include <cstdlib>


Module SegmentAws(const config& c)
{
    return Module {
    	{
    		module::id::aws,
			utils::string(std::getenv("AWS_PROFILE")),
			c.aws.theme
    	}
    };
}
