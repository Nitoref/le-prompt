#include <pwd.h>
#include <unistd.h>
#include <string.h>
#include "../modules.hpp"
#include "../utils.hpp"




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

static int fold(char* path)
{
    const char *sep = "…";
    char *stop = strnrchr(path, '/', 3);
    if (stop != NULL){
        char *start = strchr(path, '/');
        if (start != NULL && start != stop){
            memmove(start + strlen(sep) + 1, stop, path + strlen(path) - stop + 1);
            for (int i = 0; i < 3; i++)
                start[i+1] = sep[i];
            return 1;
        }

    }
    return 0;
}

void
SegmentPwd::makeSegment()
{
    segment.content = getenv("PWD");
    if (segment.content == NULL)
        return;
    
    removeHome(&segment.content);
    fold(segment.content);
    segment.style = opt.theme.Path;
};
