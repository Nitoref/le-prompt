#include <pwd.h>
#include <unistd.h>
#include <string.h>
#include "../modules.hpp"




static char* getHome()
{
    char *home = getenv("HOME");
    if (home == NULL)
        home = getpwuid(getuid())->pw_dir;
    if (home == NULL)
        return NULL;
    return home;
}

static int removeHome(char** path)
{
    char *home = getHome();
    if (home == NULL)
        return 0;
    int homeLength = strlen(home);
    if (!homeLength || strncmp(*path, home, homeLength))
        return 0;
    *path = &((*path)[homeLength - 1]);
    **path = '~';
    return 1;
}

void
SegmentPwd::makeSegment()
{
    segment.content = getenv("PWD");
    if (segment.content == NULL)
        return;
    
    removeHome(&segment.content);
    segment.style = opt->theme->Path;
};
