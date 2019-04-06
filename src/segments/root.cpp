#include <stdlib.h>
#include "../modules.hpp"


void
SegmentRoot::make()
{
    segment.content = opt.shell.indicator_;

    if (!opt.shell.prev_error_)
        segment.style = opt.theme.cmd_passed;
    else
        segment.style = opt.theme.cmd_failed;
};
