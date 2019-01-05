#ifndef SEGMENT_H
#define SEGMENT_H

#include <cstring>
#include <thread>

#include "theme.hpp"


struct Segment
{
    char* content;
    Style style;
    
    Segment(){
        content = NULL;
    };

    Segment(Style style):
        style(style)
    {};
    
    Segment(char* content):
        content(content)
    {};

    Segment(char* content, Style style):
        style(style),
        content(content)
    {};
};

#endif
