#ifndef SEGMENT_H
#define SEGMENT_H

#include <vector>
#include <string>



namespace module 
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
    
    module::id  id;
    std::string content;
    Theme       theme;
    
    // Segment(module::id c, std::string a, Theme b)
    // :content(a),theme(b),id(c)
    // {}
    // Segment(std::string a, Theme b)
    // :content(a),theme(b)
    // {}
    // Segment() = default;

    operator bool() { return !content.empty(); }
};

class Module: public std::vector<Segment>
{
    using std::vector<Segment>::vector;
    using std::vector<Segment>::operator=;

public:
    
    operator bool() { return !this->empty(); }
};


#endif
