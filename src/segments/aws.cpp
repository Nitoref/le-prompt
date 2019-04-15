#include <cstdlib>
#include "../utils.hpp"
#include "../modules.hpp"


Module SegmentAws(const Config& c)
{
    return Module {
    	{
    		module::id::aws,
			utils::string(getenv("AWS_PROFILE")),
			c.theme.aws
    	}
    };
}
