#ifndef SEGMENT_H
#define SEGMENT_H

#include <cstring>
#include <thread>

#include "theme.hpp"


struct Segment{
    char* content;
    Style style;
    Segment() = default;
    Segment(char* content, Style style){
        this->content = content;
        this->style = style;
    };
};

#endif
