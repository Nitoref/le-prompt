#include <stdlib.h>
#include "../modules.hpp"


void
SegmentRoot::make()
{
    segment.content = opt.shell.indicator_;

    if (!opt.args.prev_error)
        segment.style = opt.theme.cmd_passed;
    else
        segment.style = opt.theme.cmd_failed;
};
