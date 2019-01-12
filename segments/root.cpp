#include <stdlib.h>
#include "../modules.hpp"


void
SegmentRoot::make()
{
    segment.content = strdup(opt.shell.indicator_);

    if (opt.args.prev_error == 0)
        segment.style = opt.theme.cmd_passed;
    else
        segment.style = opt.theme.cmd_failed;
};
