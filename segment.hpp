#ifndef SEGMENT_H
#define SEGMENT_H

#include "theme.hpp"


struct Segment
{
    char* content = NULL;
    Style style;
    
    Segment() = default;

    Segment(Style style):
        style(style)
    {};
    
    Segment(char* content):
        content(content)
    {};

    Segment(char* content,
            Style style):
        style(style),
        content(content)
    {};
};

#endif
