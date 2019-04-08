#ifndef SEGMENT_H
#define SEGMENT_H

#include <string>
#include "theme.hpp"


struct Segment
{
    std::string content;
    Style style;

    operator bool()
    {
        return !content.empty();
    }
};

#endif
