#include <cstdlib>
#include <unistd.h>
#include "../modules.hpp"


Module
SegmentPerms(const config& c)
{
    char* dir = getenv("PWD");
    if (!access(dir, W_OK))
    {
        return {Segment {}};
    }

    return Module {
    	{
	    	module::id::perms,
	    	c.readonly.symbol,
	    	c.readonly.theme
    	}
    };
}
