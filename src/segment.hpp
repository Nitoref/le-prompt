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


class Segment
{

private:

    segment::id  id_;
    Theme        theme_;
    size_t       length_;
    std::string  content_;


public:

    Segment(segment::id id):
    id_ (id)
    {}
    Segment() = default;

    operator bool()
    {
        return !content_.empty();
    }

    segment::id id()
    {
        return id_;
    }
    
    std::string
    content()
    {
        return content_;
    }

    Theme
    theme()
    {
        return theme_;
    }

    size_t
    length()
    {
        return length_;
    }


    void
    identify(segment::id id)
    {
        id_ = id;
    }
    
    void
    theme(Theme t)
    {
        theme_ = t;
    }
    
    void
    append(char c)
    {
        length_  ++;
        content_ += printer::escape(c);
    }
    void
    append(std::string s)
    {
        length_  += utils::strlen(s);
        content_ += printer::escape(s);
    }

    Segment&
    operator +=(std::string s)
    {
        append(s);
        return *this;
    }

    void
    append(std::string s, Theme t)
    {
        content_ += printer::fg(t.fg);
        append(s);
    }
};





#endif
