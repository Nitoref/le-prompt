#include <stdlib.h>
#include "../segments.hpp"


Segment* segmentRoot(PromptOpt *p)
{
    Style style;
    if (p -> args -> PrevError == 0)
        style = p->theme->CmdPassed;
    else
        style = p->theme->CmdFailed;

    return new Segment(strdup(p->shell->rootIndicator), style);
}
