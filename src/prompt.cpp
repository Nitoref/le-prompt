#include "prompt.hpp"
#include "utils.hpp"

#include <future>
#include <chrono>
#include <string>


Prompt::Prompt(PromptConfig options):
    options(options),
    printer(options.shell)
{}


void
Prompt::make_segments()
{
    std::vector<std::future<Segment>> left_futures;
    std::vector<std::future<Segment>> right_futures;

    for (auto str: options.args.left_segments) {
        if (auto fun = get_segment_by_name(str)) {
            left_futures.push_back( std::async(
                std::launch::async,
                [=](){ return (*fun)(options);})
            );
        }
    }

    for (auto str: options.args.right_segments) {
        if (auto fun = get_segment_by_name(str)) {
            right_futures.push_back( std::async(
                std::launch::async,
                [=](){ return (*fun)(options);})
            );
        }
    }

    for (auto& future: left_futures) {
        auto status = future.wait_for(std::chrono::seconds(1));
        if (status == std::future_status::timeout) {
            left_segments_.push_back(Segment{"408", {5, 12}});
        }
        if (auto segment = future.get()) {
            left_segments_.push_back(segment);
        }
    }
    for (auto& future: right_futures) {
        auto status = future.wait_for(std::chrono::seconds(1)) ;
        if (status== std::future_status::timeout) {
            right_segments_.push_back(Segment{"408", {5, 12}});
        }
        if (auto segment = future.get()) {
            right_segments_.push_back(segment);
        }
    }
}

std::string
Prompt::make_separator(Segment s, std::string regular, std::string thin)
{
    std::string output;
    if (s.style.bg == prev_color_) {
        output += printer.fg(options.theme.separator.fg);
        output += thin;
    }
    else
    if (prev_color_ != -1) {
        output += printer.bg(s.style.bg);
        output += printer.fg(prev_color_);
        output += regular;
    }
    prev_color_ = s.style.bg;
    return output;
}

std::string
Prompt::format_segment(Segment s) 
{
    std::string output;
    output += printer.bg(s.style.bg);
    output += printer.fg(s.style.fg);
    output += ' ';
    output += s.content;
    output += ' ';
    return output;
}

std::string
Prompt::end_prompt(std::string separator) 
{
    std::string output;
    output += printer.reset();
    output += printer.fg(prev_color_);
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
        output += printer.reset();
    }
    return output;
}

std::string
Prompt::format_left_segments()
{
    return format_segments(
        left_segments_, utils::string::append,
        options.symbols.separator, options.symbols.separator_thin
    );
}

std::string
Prompt::format_right_segments()
{
    return format_segments(
        right_segments_, utils::string::prepend,
        options.symbols.r_separator, options.symbols.r_separator_thin
    );
}



size_t
Prompt::length(std::vector<Segment> segments)
{
    size_t length = 0;
    int color = -1;
    for (auto& segment: segments) {
        if (segment.style.bg == color) {
            length += utils::string::length(options.symbols.separator);
        } 
        else {
            length += utils::string::length(options.symbols.separator_thin);
        }
        length += 2 + utils::string::length(segment.content);
        color = segment.style.bg;
    }
    return length + 1;
}
size_t
Prompt::right_length()
{
    return length (right_segments_);
}
size_t
Prompt::left_length()
{
    return length (left_segments_);
}
