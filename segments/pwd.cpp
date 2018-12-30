#include <pwd.h>
#include <unistd.h>
#include <string.h>


#include "../segments.hpp"


char* getHome()
{
    char *home = getenv("HOME");
    if (home == NULL)
        home = getpwuid(getuid())->pw_dir;
    if (home == NULL)
        return NULL;
    return home;
}

int removeHome(char** path)
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

Segment* segmentPwd(PromptOpt *p) {

    char *path = getenv("PWD");
    if (path == NULL)
        return NULL;
    
    removeHome(&path);

    return new Segment(path, p->theme->Path);
}
