#include <string>
#include <cstddef>

#include <unistd.h>
// #include <string.h>
// #include <stdlib.h>

#include "segments.hpp"

Segment segmentHost(Prompt *p)
{
    char *hostname = (char*)malloc(HOSTNAME_MAX);
    gethostname(hostname, HOSTNAME_MAX);
    if (hostname == nullptr)
        return nullptr;

    char *delimiter = strstr(hostname, ".");
    if (delimiter != nullptr)
        *delimiter = '\0';

    return Segment(std::string(hostname), p->theme->Hostname);
}
