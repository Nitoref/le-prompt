#include "prompt.hpp"
#include "utils.hpp"

#include <future>
#include <string>


Prompt::Prompt(PromptConfig options):
    options_(options),
    printer_(options.shell)
{}


void
Prompt::make_segments()
{
    std::vector<std::future<Segment>> left_futures;
    std::vector<std::future<Segment>> right_futures;

    for (auto str: options_.args.left_segments) {
        if (auto fun = get_segment_by_name(str)) {
            left_futures.push_back( std::async(
                std::launch::async,
                [=](){ return (*fun)(options_);})
            );
        }
    }

    for (auto str: options_.args.right_segments) {
        if (auto fun = get_segment_by_name(str)) {
            right_futures.push_back( std::async(
                std::launch::async,
                [=](){ return (*fun)(options_);})
            );
        }
    }

    for (auto& future: left_futures) {
        if (future.wait(); Segment segment = future.get()) {
            left_segments_.push_back(segment);
        }
    }
    for (auto& future: right_futures) {
        if (future.wait(); Segment segment = future.get()) {
            right_segments_.push_back(segment);
        }
    }
}

std::string
Prompt::make_separator(Segment s, std::string regular, std::string thin)
{
    std::string output;
    if (s.style.bg == prev_color_) {
        output += printer_.fg(options_.theme.separator.fg);
        output += thin;
    }
    else
    if (prev_color_ != -1) {
        output += printer_.bg(s.style.bg);
        output += printer_.fg(prev_color_);
        output += regular;
    }
    prev_color_ = s.style.bg;
    return output;
}

std::string
Prompt::format_segment(Segment s) 
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
Prompt::end_prompt(std::string separator) 
{
    std::string output;
    output += printer_.reset();
    output += printer_.fg(prev_color_);
    output += separator;
    prev_color_ = -1;
    return output;
}

std::string
Prompt::format_segments(
    std::vector<Segment> segments, 
    std::function<void(std::string&, std::string)> add,
    std::string regular, std::string thin)
{
    std::string output;
    for (auto &segment : segments) {
        add(output, make_separator(segment, regular, thin));
        add(output, format_segment(segment));
    }
    if (!output.empty()){
        add(output, end_prompt(regular));
        output += printer_.reset();
    }
    return output;
}

std::string
Prompt::format_left_segments()
{
    return format_segments(
        left_segments_, utils::string::append,
        options_.symbols.separator, options_.symbols.separator_thin
    );
}

std::string
Prompt::format_right_segments()
{
    return format_segments(
        right_segments_, utils::string::prepend,
        options_.symbols.r_separator, options_.symbols.r_separator_thin
    );
}



size_t
Prompt::left_length()
{
    size_t length = 0;
    for (auto& segment: left_segments_) {
        length += 2 + utils::string::length(segment.content);
        length += utils::string::length(options_.symbols.separator);
    }
    return length + 1;
}
size_t
Prompt::right_length()
{
    size_t length = 0;
    for (auto& segment: right_segments_) {
        length += 2 + utils::string::length(segment.content);
        length += utils::string::length(options_.symbols.r_separator);
    }
    return length + 1;
}
