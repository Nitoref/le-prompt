#include <stdlib.h>
#include <unistd.h>

#include "../segments.hpp"


Segment* segmentUser(PromptOpt *p)
{
    Style style;
    char *user;
    user = getenv("USER");

    if (user == NULL)
        return NULL;
    if (getuid() != 0)
        style = p->theme->Username;
    else
        style = p->theme->UsernameRoot;

    return new Segment(user, style);
}
