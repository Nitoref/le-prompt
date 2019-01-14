#include "prompt.hpp"
#include "utils.hpp"

#include <iostream>
#include <string>
#include <sstream>


Prompt::Prompt(PromptOpt options):
    options_(options),
    printer_(options.shell)
{
    segments_ = {
        {"user", new SegmentUser(this->options_)},
        {"root", new SegmentRoot(this->options_)},
        {"pwd",  new SegmentPwd(this->options_)},
        {"exit", new SegmentExit(this->options_)},
        {"git",  new SegmentGit(this->options_)},
        {"host", new SegmentHost(this->options_)},
        {"nl",   new SegmentNewline(this->options_)},
    };
    threads_.reserve(segments_.size());
}

ThreadedSegment*
Prompt::get_segment_by_name(std::string str)
{
    auto& s = segments_[str];
    return s ? : NULL;
}

void
Prompt::parse_left_segments(std::vector<std::string> segments)
{
    for (auto& segment: options_.args.left_segments)
    {
        if (ThreadedSegment *s = get_segment_by_name(segment)){
            s->init();
            threads_.push_back(s);
        }
    }
}

void
Prompt::parse_right_segments(std::vector<std::string> segments)
{
    for (auto& segment: options_.args.right_segments)
    {
        if (ThreadedSegment *s = get_segment_by_name(segment)){
            s->init();
            right_threads_.push_back(s);
        }
    }
}

void
Prompt::parse_left_segments()
{
    parse_left_segments(options_.args.left_segments);
}
void
Prompt::parse_right_segments()
{
    parse_right_segments(options_.args.right_segments);
}

void
Prompt::print_left()
{
    for (auto &thread : threads_)
    {
        thread->join();
        if (!thread->segment.content)
        {
            continue;
        }
        print_segment(thread->segment);
    }
    reset();
}

void
Prompt::print_right()
{
    for (auto &thread : right_threads_)
    {
        thread->join();
        if (!thread->segment.content)
        {
            continue;
        }
        print_r_segment(thread->segment);
    }
    printer_.reset_style();
}

void
Prompt::print_segment(Segment s)
{
    if (s.style.bg == prev_color_)
    {
        length_ += strlen_utf8(options_.symbols.separator_thin);
        printer_.set_fg(s.style.fg);
        printf("%s", options_.symbols.separator_thin);
    }
    else
    if (prev_color_ != -1)
    {
        length_ += strlen_utf8(options_.symbols.separator);
        printer_.set_bg(s.style.bg);
        printer_.set_fg(prev_color_);
        printf("%s", options_.symbols.separator);
    }
    printer_.set_bg(s.style.bg);
    printer_.set_fg(s.style.fg);
    printf(" %s ",s.content);
    length_ += strlen_utf8(s.content) + 2;
    prev_color_ = s.style.bg;
}

void
Prompt::print_r_segment(Segment s)
{
    if (s.style.bg == prev_color_)
    {
        length_ += strlen_utf8(options_.symbols.r_separator_thin);
        printer_.set_bg(s.style.fg);
        printf("%s", options_.symbols.r_separator_thin);
    }
    else
    {
        length_ += strlen_utf8(options_.symbols.r_separator);
        if (prev_color_ != -1)
            printer_.set_bg(prev_color_);
        printer_.set_fg(s.style.bg);
        printf("%s", options_.symbols.r_separator);
    }
    printer_.set_bg(s.style.bg);
    printer_.set_fg(s.style.fg);
    printf(" %s ",s.content);
    length_ += strlen_utf8(s.content) + 2;
    prev_color_ = s.style.bg;
}

void
Prompt::reset(){
    printer_.reset_style();
    printer_.set_fg(prev_color_);
    printf("%s  ", options_.symbols.separator);
    printer_.reset_style();
}



// g++ -Oz -o build/powerline -std=c++17 *.cpp ./*/*.cpp -lgit2 -Iinclude
// clang++ -std=c++2a -Wall -Werror -D_LIBCPP_DISABLE_AVAILABILITY test.cpp -I/Users/nitoref/Desktop/powerless/C++/include/
