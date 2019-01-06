#include <stdlib.h>
#include "../modules.hpp"


void
SegmentRoot::makeSegment()
{
    segment.content = strdup(opt.shell.rootIndicator);

    if (opt.args.PrevError == 0)
        segment.style = opt.theme.CmdPassed;
    else
        segment.style = opt.theme.CmdFailed;
};
