#define HOSTNAME_MAX 256

#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "../segments.hpp"


Segment* segmentHost(PromptOpt *p) {
    char *hostname = (char*)malloc(HOSTNAME_MAX);
    gethostname(hostname, HOSTNAME_MAX);

    char *delimiter = strchr(hostname, '.');
    if (delimiter != NULL)
        *delimiter = '\0';        

    return new Segment(hostname, p->theme->Hostname);
};
