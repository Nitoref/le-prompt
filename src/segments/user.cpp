#include <cstdlib>
#include <unistd.h>
#include "../modules.hpp"
#include "../utils.hpp"


void
SegmentUser::make()
{
    segment.content = utils::string::safe(getenv("USER"));

    if (getuid() != 0)
        segment.style = opt.theme.username;
    else
        segment.style = opt.theme.username_root;
};
