#ifndef SEGMENT_H
#define SEGMENT_H

#include <vector>
#include <string>

#include "utils.hpp"
#include "theme.hpp"
#include "printer.hpp"


namespace segment
{

enum class id: unsigned int;

}

struct Segment
{
    
    segment::id  id;
    std::string content;
    Theme       theme;

    operator bool() {
        return !content.empty();
    }
};


class Module: public std::vector<Segment>
{
    using std::vector<Segment>::vector;
    using std::vector<Segment>::operator=;

public:
    
    operator bool() { return !this->empty(); }
};





#endif
