#include <cstdlib>
#include <unistd.h>
#include "../modules.hpp"


Module
SegmentPerms(const Config& c)
{
    char* dir = getenv("PWD");
    if (!access(dir, W_OK))
    {
        return {Segment {}};
    }

    return Module {
    	{
	    	module::id::perms,
	    	c.symbols.readonly,
	    	c.theme.readonly
    	}
    };
}
