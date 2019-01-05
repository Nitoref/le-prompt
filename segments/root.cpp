#include <stdlib.h>
#include "../modules.hpp"



Segment*
SegmentRoot::makeSegment()
{
    Style style;
    if (opt -> args -> PrevError == 0)
        style = opt->theme->CmdPassed;
    else
        style = opt->theme->CmdFailed;

    return new Segment(strdup(opt->shell->rootIndicator), style);
};
