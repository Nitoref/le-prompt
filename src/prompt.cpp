#include "prompt.hpp"
#include "utils.hpp"

#include <iostream>
#include <string>
#include <sstream>


Prompt::Prompt(PromptConfig options):
    options_(options),
    printer_(options.shell)
{
    segments_map_ = {
        {"user", new SegmentUser(this->options_)},
        {"root", new SegmentRoot(this->options_)},
        {"pwd",  new SegmentPwd(this->options_)},
        {"exit", new SegmentExit(this->options_)},
        {"host", new SegmentHost(this->options_)},
        {"jobs", new SegmentJobs(this->options_)},
        {"git",  new SegmentGit(this->options_)},
        {"time", new SegmentTime(this->options_)},
    };
}

ThreadedSegment*
Prompt::get_segment_by_name(std::string str)
{
    // auto s = segments_map_[str];
    // return s ? : nullptr;
    if (auto& s = segments_map_.find(str); s != segments_map_.end())
        return s->second;
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
    parse_segments(options_.args.left_segments, l_segments_);
    parse_segments(options_.args.right_segments, r_segments_);
}


std::string
Prompt::merge_segments(std::vector<ThreadedSegment*>& threads, std::string(Prompt::*f)(Segment))
{
    std::string output;
    for (auto &thread : threads)
    {
        thread->join();
        if (!thread->segment.content.empty())
        {
            output += (this->*f)(thread->segment);
        }
    }
    return output;
}

std::string
Prompt::print_left_segments()
{
    std::string output;
    output += merge_segments(l_segments_, &Prompt::print_left_segment);
    output += printer_.reset();
    output += printer_.fg(prev_color_);
    output += options_.symbols.separator;
    output += printer_.reset();
    prev_color_ = -1;
    return output;
}

std::string
Prompt::print_right_segments()
{
    std::string output;
    output += merge_segments(r_segments_, &Prompt::print_right_segment);
    output += printer_.reset();
    prev_color_ = -1;
    return output;
}

std::string
Prompt::print_left_segment(Segment s)
{
    std::string output;
    if (s.style.bg == prev_color_)
    {
        output += printer_.fg(s.style.fg);
        output += options_.symbols.separator_thin;
    }
    else
    if (prev_color_ != -1)
    {
        output += printer_.bg(s.style.bg);
        output += printer_.fg(prev_color_);
        output += options_.symbols.separator;
    }
    output += printer_.bg(s.style.bg);
    output += printer_.fg(s.style.fg);
    output += ' ';
    output += s.content;
    output += ' ';
    prev_color_ = s.style.bg;
    return output;
}

std::string
Prompt::print_right_segment(Segment s)
{
    std::string output;
    if (s.style.bg == prev_color_)
    {
        output += printer_.fg(s.style.fg);
        output += options_.symbols.r_separator_thin;
    }
    else
    {
        if (prev_color_ != -1){
            output += printer_.bg(prev_color_);
        }
        output += printer_.fg(s.style.bg);
        output += options_.symbols.r_separator;
    }
    output += printer_.bg(s.style.bg);
    output += printer_.fg(s.style.fg);
    output += ' ';
    output += s.content;
    output += ' ';
    prev_color_ = s.style.bg;
    return output;
}


size_t
Prompt::right_length()
{
    size_t length = 0;
    for (auto& thread: r_segments_)
        if (!thread->segment.content.empty())
            length += 3 + utils::string::length(thread->segment.content);
    return length + 1;
}
size_t
Prompt::left_length()
{
    size_t length = 0;
    for (auto& thread: l_segments_)
        if (!thread->segment.content.empty())
            length += 3 + utils::string::length(thread->segment.content);
    return length + 1;
}
