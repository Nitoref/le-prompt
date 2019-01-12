#include <stdlib.h>
#include <unistd.h>
#include "../modules.hpp"


void
SegmentUser::make()
{
    segment.content = getenv("USER");

    if (getuid() != 0)
        segment.style = opt.theme.username;
    else
        segment.style = opt.theme.username_root;
};
