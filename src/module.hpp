#ifndef SEGMENT_H
#define SEGMENT_H

#include "theme.hpp"
#include <vector>
#include <string>


namespace module 
{
enum class id: unsigned int;
}

struct Segment
{
    std::string content;
    Style style;
    module::id id;
    
    Segment(module::id c, std::string a, Style b):content(a),style(b),id(c)
    {}
    Segment(std::string a, Style b):content(a),style(b)
    {}
    Segment() = default;

    operator bool() { return !content.empty(); }
};

struct Module: public std::vector<Segment>
{
	using std::vector<Segment>::vector;
    using std::vector<Segment>::operator=;

    operator bool() { return !this->empty(); }
};


#endif
