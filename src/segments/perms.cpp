#include <cstdlib>
#include <unistd.h>
#include "segments.hpp"


Segment SegmentPerms(PromptConfig p)
{
	Segment segment;
    char* cwd = getenv("PWD");
    if (!access(cwd, W_OK)) {
        return Segment {};
    }
	segment.content = p.symbols.lock;
    segment.style = p.theme.readonly;
    return segment;
}
