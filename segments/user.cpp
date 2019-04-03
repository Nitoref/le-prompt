#include <stdlib.h>
#include <unistd.h>
#include "../modules.hpp"
#include "../string.hpp"


void
SegmentUser::make()
{
    segment.content = string {getenv("USER")};

    if (getuid() != 0)
        segment.style = opt.theme.username;
    else
        segment.style = opt.theme.username_root;
};
