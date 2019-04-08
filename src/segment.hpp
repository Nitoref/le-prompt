#ifndef SEGMENT_H
#define SEGMENT_H

#include <vector>
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

struct MultiSegment: public std::vector<Segment>
{
	using std::vector<Segment>::vector;

    operator bool()
    {
        return !this->empty();
    }
};

#endif
