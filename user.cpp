#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "theme.h"
#include "segments.hpp"


Segment segmentUser(Prompt *p)
{
    char *user;
    user = getenv("USER");

    if (user == NULL)
        return NULL;
    
    Style style;

    if (getuid() != 0)
        style = p->theme->Username;
    else
        style = p->theme->UsernameRoot;

    return Segment(user, style);
}
