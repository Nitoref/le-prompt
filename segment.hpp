#ifndef SEGMENT_H
#define SEGMENT_H

#include "theme.hpp"
#include "utils.hpp"


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
        content(content),
        style(style)
    {};

    size_t length()
    {
        return strlen_utf8(content);
    }
};

#endif
