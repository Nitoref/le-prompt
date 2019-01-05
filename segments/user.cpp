#include <stdlib.h>
#include <unistd.h>
#include "../modules.hpp"


Segment*
SegmentUser::makeSegment()
{
    Style style;
    char *user;
    user = getenv("USER");

    if (user == NULL)
        return NULL;
    if (getuid() != 0)
        style = opt->theme->Username;
    else
        style = opt->theme->UsernameRoot;

    return new Segment(user, style);
};
