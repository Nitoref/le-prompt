#include <cstdlib>
#include "../utils.hpp"
#include "../modules.hpp"


Module SegmentAws(const config& c)
{
    return Module {
    	{
    		module::id::aws,
			utils::string(getenv("AWS_PROFILE")),
			c.aws.theme
    	}
    };
}
