#ifndef SEGMENT_H
#define SEGMENT_H

#include <vector>
#include <string>



namespace segment
{
enum class id: unsigned int;
}

struct Theme
{
    int   fg = -1;
    int   bg = -1;
};


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
