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
    std::string  content_;
    Theme        theme_;
    size_t       escapes_ = 0;


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
    
    std::string&
    content()
    {
        return content_;
    }

    Theme&
    theme()
    {
        return theme_;
    }

    size_t
    length()
    {
        return utils::strlen(content_);
    }

    void
    theme(Theme t)
    {
        theme_ = t;
    }
    
    void
    append(char c)
    {
        content_ += printer::escape(c);
    }
    void
    append(std::string s)
    {
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
        std::string style;
        style += printer::fg(t.fg);
        style += printer::bg(t.bg);
        // for (auto& font: t.
        escapes_ += style.length();
        content_ += style;
        append(s);
    }
};





#endif
