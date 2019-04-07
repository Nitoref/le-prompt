#include "prompt.hpp"
#include "utils.hpp"

#include <functional>
#include <iostream>
#include <string>
#include <sstream>


Prompt::Prompt(PromptConfig options):
    options_(options),
    printer_(options.shell)
{
    segments_map_ = {
        {"user", [this]() -> ThreadedSegment* {return new SegmentUser(this->options_);}},
        {"root", [this]() -> ThreadedSegment* {return new SegmentRoot(this->options_);}},
        {"pwd",  [this]() -> ThreadedSegment* {return new SegmentPwd(this->options_);}},
        {"exit", [this]() -> ThreadedSegment* {return new SegmentExit(this->options_);}},
        {"host", [this]() -> ThreadedSegment* {return new SegmentHost(this->options_);}},
        {"jobs", [this]() -> ThreadedSegment* {return new SegmentJobs(this->options_);}},
        {"git",  [this]() -> ThreadedSegment* {return new SegmentGit(this->options_);}},
        {"time", [this]() -> ThreadedSegment* {return new SegmentTime(this->options_);}},
    };
}

ThreadedSegment*
Prompt::get_segment_by_name(std::string str)
{
    if (auto s = segments_map_.find(str); s != segments_map_.end())
        return (s->second)();
    return nullptr;
}


void
Prompt::parse_segments(std::vector<std::string> list, std::vector<ThreadedSegment*>& threads)
{
    for (auto& segment: list)
    {
        if (ThreadedSegment *s = get_segment_by_name(segment))
        {
            s->init();
            threads.push_back(s);
        }
    }
}

void
Prompt::parse_segments()
{
    parse_segments(options_.args.left_segments, left_threads_);
    parse_segments(options_.args.right_segments, right_threads_);
}



std::string
Prompt::make_separator(Segment s, bool left)
{
    std::string output;
    std::string separator  = left ? "" : "";
    std::string separatort = left ? "" : "";
    if (s.style.bg == prev_color_)
    {
        output += printer_.fg(s.style.fg);
        output += separatort;
    }
    else
    if (prev_color_ != -1)
    {
        output += printer_.bg(s.style.bg);
        output += printer_.fg(prev_color_);
        output += separator;
    }
    prev_color_ = s.style.bg;
    return output;
}

std::string
Prompt::print_segment(Segment s) 
{
    std::string output;
    output += printer_.bg(s.style.bg);
    output += printer_.fg(s.style.fg);
    output += ' ';
    output += s.content;
    output += ' ';
    return output;
}


std::string
Prompt::print_left_segments()
{
    std::string output;
    for (auto &thread : left_threads_) {
        thread->join();
        if (!thread->segment.content.empty()) {
            output += make_separator(thread->segment, 1);
            output += print_segment(thread->segment);
            // output += print_left_segment(thread->segment);
        }
    }
    output += printer_.reset();
    output += printer_.fg(prev_color_);
    output += options_.symbols.separator;
    
    prev_color_ = -1;
    return output;
}

std::string
Prompt::print_right_segments()
{
    std::string output;
    for (auto &thread : right_threads_) {
        thread->join();
        if (!thread->segment.content.empty()) {
            output.insert(0, make_separator(thread->segment, 0));
            output.insert(0, print_segment(thread->segment));
            // output.insert(0, print_right_segment(thread->segment));
        }
    }
    output.insert(0, options_.symbols.r_separator);
    output.insert(0, printer_.fg(prev_color_));
    
    output += printer_.reset();
    prev_color_ = -1;
    return output;
}











size_t
Prompt::right_length()
{
    size_t length = 0;
    for (auto& thread: right_threads_)
        if (!thread->segment.content.empty())
            length += 3 + utils::string::length(thread->segment.content);
    return length + 1;
}
size_t
Prompt::left_length()
{
    size_t length = 0;
    for (auto& thread: left_threads_)
        if (!thread->segment.content.empty())
            length += 3 + utils::string::length(thread->segment.content);
    return length + 1;
}
