#include <stdlib.h>
#include "../segments.hpp"


Segment
SegmentRoot(PromptConfig p)
{
	Segment segment;
    segment.content = p.shell.indicator;

    if (!p.shell.prev_error_)
    {
        segment.style = p.theme.cmd_passed;
    }
    else
    {
        segment.style = p.theme.cmd_failed;
    }

    return segment;
};
