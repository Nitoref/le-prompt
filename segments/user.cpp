#include <stdlib.h>
#include <unistd.h>
#include "../modules.hpp"


void
SegmentUser::makeSegment()
{
    segment.content = getenv("USER");

    if (getuid() != 0)
        segment.style = opt.theme.Username;
    else
        segment.style = opt.theme.UsernameRoot;
};
