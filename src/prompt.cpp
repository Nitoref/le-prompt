#include "arguments.hpp"
#include "symbols.hpp"
#include "prompt.hpp"
#include "theme.hpp"
#include "shell.hpp"
#include "utils.hpp"

#include <string>
#include <iostream>
#include <algorithm>
#include <functional>
#include <unordered_map>


Prompt::Prompt(Config config):options(config)
{
    printer = Printer(options.shell.id);
}

void
Prompt::shrink()
{
    std::vector<std::vector<int>> right_lookup ((int)module::id::Count);
    std::vector<std::vector<int>> left_lookup ((int)module::id::Count);
    
    for (size_t i = 0; i <right_segments.size(); ++i)
    {
        right_lookup.at((int)right_segments[i].id).push_back(i);
    }
    for (size_t i = 0; i < left_segments.size(); ++i)
    {
        left_lookup.at((int)left_segments[i].id).push_back(i);
    }

    left_length_  = length (left_segments);
    right_length_ = length (right_segments);

    for (auto i = priority_list_.rbegin(); i != priority_list_.rend(); ++i)
    {
        for (auto index: left_lookup.at((int)*i))
        {
            left_length_ -= utils::string::length(left_segments[index].content) + 3;
        }
        for (auto index: right_lookup.at((int)*i))
        {
            right_length_ -= utils::string::length(right_segments[index].content) + 3;
        }
        ignored_segments_.insert(*i);
        if (left_length_ + right_length_ < options.shell.width - 30)
            return;
    }
}

std::string
Prompt::print()
{
    std::string output;
    switch (options.shell.id)
    {
    case Shell::Type::bash:
    case Shell::Type::csh:
    case Shell::Type::tcsh:
    {
        printer.wrap_mode(false);
        output += printer.wrap;
        output += printer.cup(options.shell.width - right_length_ + 2);
        output += format_right_segments();
        output += printer.cup(0);
        output += printer.unwrap;
        printer.wrap_mode(true);
        output += format_left_segments();
        output += " ";
        break;
    }
    case Shell::Type::zsh:
    case Shell::Type::fish:
    default:
        printer.wrap_mode(true);
        output += format_left_segments();
        output += '\n';
        output += format_right_segments();
    }
    return output;
}


std::string
Prompt::make_separator(Segment s, std::string regular, std::string thin)
{
    std::string output;
    if (s.style.bg == prev_color_)
    {
        output += printer.fg(options.theme.separator.fg);
        output += thin;
    }
    else
    if (prev_color_ != -1)
    {
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
    output += std::string(options.args.padding, ' ');
    output += s.content;
    output += std::string(options.args.padding, ' ');
    return output;
}

std::string
Prompt::end_separator(std::string separator) 
{
    std::string output;
    output += printer.reset();
    output += printer.fg(prev_color_);
    output += separator;
    prev_color_ = -1;
    return output;
}

std::string
Prompt::format_segments(std::vector<Segment> segments, bool policy)
{
    std::string regular, thin;
    std::function<void(std::string&, std::string)> append;
    if (policy == true)
    {
        regular = options.symbols.separator;
        thin = options.symbols.separator2;
        append = utils::string::append;
    }
    else
    {
        regular = options.symbols.rseparator;
        thin = options.symbols.rseparator2;
        append = utils::string::prepend;
    }

    std::string output;
    for (auto &segment : segments)
    {
        if (ignored_segments_.find(segment.id) != ignored_segments_.end())
            continue;
        append(output, make_separator(segment, regular, thin));
        append(output, format_segment(segment));
    }
    if (!output.empty())
    {
        append(output, end_separator(regular));
        output += printer.reset();
    }
    return output;
}

std::string
Prompt::format_left_segments()
{
    return format_segments(left_segments, true);
}

std::string
Prompt::format_right_segments()
{
    return format_segments(right_segments, false);
}


size_t
Prompt::length(std::vector<Segment> segments)
{
    int color = -1;
    size_t total = 0;

    size_t separator = utils::string::length(options.symbols.separator);
    size_t rseparator = utils::string::length(options.symbols.rseparator);
    
    for (auto& segment: segments)
    {
        total += segment.style.bg == color ? separator : rseparator;
        total += utils::string::length(segment.content);
        total += options.args.padding * 2;
        
        color = segment.style.bg;
    }
    return total + 1;
}
