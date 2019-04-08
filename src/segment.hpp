#ifndef SEGMENT_H
#define SEGMENT_H

#include <string>
#include "theme.hpp"
#include "utils.hpp"


struct Segment
{
    std::string content;
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

    operator bool() {
        return !content.empty();
    }
};

#endif
