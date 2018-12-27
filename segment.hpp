#ifndef SEGMENT_H
#define SEGMENT_H

#include <cstdint>
#include "theme.hpp"

struct Segment
{
    Segment(std::string content, Style style);
    std::string content;
    Style style;
};



#endif
