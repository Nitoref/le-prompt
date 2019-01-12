#define HOSTNAME_MAX 256

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "../modules.hpp"



void
SegmentHost::make()
{
    segment.content = (char*)malloc(HOSTNAME_MAX);
    gethostname(segment.content, HOSTNAME_MAX);

    char *delimiter = strchr(segment.content, '.');
    if (delimiter != NULL)
        *delimiter = '\0';

    segment.style = opt.theme.hostname;
};
