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

Segment*
SegmentPwd::getSegment()
{
    char *path = getenv("PWD");
    if (path == NULL)
        return NULL;
    
    removeHome(&path);

    return new Segment(path, opt->theme->Path);
};
