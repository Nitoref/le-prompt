#include <cstdlib>
#include <unistd.h>
#include "modules.hpp"


Module
SegmentPerms(Config c)
{
	Segment segment;
    char* cwd = getenv("PWD");
    if (!access(cwd, W_OK)) {
        return {Segment {}};
    }
	segment.content = c.symbols.lock;
    segment.style = c.theme.readonly;
    segment.id = module::id::perms;
    return Module {segment};
}
