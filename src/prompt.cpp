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


Prompt::Prompt(Config& config):
options(config),
printer(options.shell.id)
{}


std::string
Prompt::print()
{
    std::string output;
    
    this->shrink();
    auto align = options.shell.width - right_length_ + 2;
    
    switch (options.shell.id)
    {
        case Shell::Type::zsh:
        case Shell::Type::fish:    
        {
            printer.wrap_mode(true);
            
            if (!newline_segments.empty() || options.args.force_newline)
            {
                output += options.symbols.top_prefix;
                output += format_left_segments();
                output += printer.cup(align);
                output += format_right_segments();
                output += "\n";
                output += options.symbols.bot_prefix;
                output += format_newline_segments();
                output += std::string(options.args.padding_end, ' ');
            }
            else
            {
                output += "\n";
                output += format_left_segments();
                output += std::string(options.args.padding_end, ' ');
                output += "\n";
                output += format_right_segments();
            }
            break;
        }
        default:
        {
            printer.wrap_mode(false);
            
            output += printer.wrap;
            output += printer.cup(align);
            output += format_right_segments();
            output += printer.cup(0);
            output += printer.unwrap;
            
            printer.wrap_mode(true);
            
            if (!newline_segments.empty() || options.args.force_newline)
            {
                output += options.symbols.top_prefix;
                output += format_left_segments();
                output += printer.newline;
                output += options.symbols.bot_prefix;
                output += format_newline_segments();
            }
            else
            {
                output += format_left_segments();
            }
            output += std::string(options.args.padding_end, ' ');
            
            if (options.shell.id == Shell::Type::csh)
                output += " %{\x1b[D%}";
            
            break;
        }
    }
    return output;
}



void
Prompt::shrink()
{
    left_length_  = length (left_segments, position::left);
    right_length_ = length (right_segments, position::right);
    if (left_length_ + right_length_ < 0.5 * options.shell.width)
    {
        return;
    }

    // std::vector<std::vector<int>> right_lookup ((int)module::id::__count);
    // std::vector<std::vector<int>> left_lookup ((int)module::id::__count);
    
    // for (size_t i = 0; i <right_segments.size(); ++i)
    // {
    //     right_lookup.at((int)right_segments[i].id).push_back(i);
    // }
    // for (size_t i = 0; i < left_segments.size(); ++i)
    // {
    //     left_lookup.at((int)left_segments[i].id).push_back(i);
    // }

    for (auto i = priority_list_.rbegin(); i != priority_list_.rend(); ++i)
    {
        for (auto index: id_lookup_left_.at((int)*i))
        {
            left_length_ -= left_lengths_[index];
            // left_length_ -= utils::strlen(left_segments[index].content);
            // left_length_ -= utils::strlen(options.symbols.separator);
            // left_length_ -= options.args.padding_left + options.args.padding_right;
        }
        for (auto index: id_lookup_right_.at((int)*i))
        {
            right_length_ -= right_lengths_[index];
            // right_length_ -= utils::strlen(right_segments[index].content);
            // right_length_ -= utils::strlen(options.symbols.rseparator);
            // right_length_ -= options.args.padding_left + options.args.padding_right;
        }
        ignored_segments_.insert(*i);
        if (left_length_ + right_length_ < 0.5 * options.shell.width)
        {
            return;
        }
    }
}


std::string
Prompt::format_segment(Segment s) 
{
    std::string output;
    output += printer.bg(s.style.bg);
    output += printer.fg(s.style.fg);
    output += std::string(options.args.padding_left, ' ');
    output += s.content;
    output += std::string(options.args.padding_right, ' ');
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
    if (prev_color_ == -1)
    {
        output += printer.fg(s.style.bg);
        output += printer.bg(prev_color_);
        output += printer.font("reversed");
        output += regular;
        output += printer.reset();
    }
    else
    if (prev_color_ != -2)
    {
        output += printer.fg(prev_color_);
        output += printer.bg(s.style.bg);
        output += regular;
    }
    prev_color_ = s.style.bg;
    return output;
}

std::string
Prompt::final_separator(std::string regular, std::string thin)
{
    std::string output;
    output += printer.reset();
    output += printer.fg(prev_color_);
    output += prev_color_ == -1 ? "" : regular;
    prev_color_ = -2;
    return output;
}


std::string
Prompt::format_left_segments()
{
    return format_segments(left_segments, position::left);
}

std::string
Prompt::format_right_segments()
{
    return format_segments(right_segments, position::right);
}

std::string
Prompt::format_newline_segments()
{
    return format_segments(newline_segments, position::left);
}


std::string
Prompt::format_segments(std::vector<Segment> segments, position pos)
{
    std::string regular, thin;
    std::function<void(std::string&, std::string)> append;
    if (pos == position::left)
    {
        regular = options.symbols.separator;
        thin    = options.symbols.separator2;
        append  = utils::str_append;
    }
    else
    {
        regular = options.symbols.rseparator;
        thin    = options.symbols.rseparator2;
        append  = utils::str_prepend;
    }

    std::string output;
    for (auto &segment : segments)
    {
        auto ignored = ignored_segments_.find(segment.id);
        if (ignored != ignored_segments_.end())
            continue;
        append(output, make_separator(segment, regular, thin));
        append(output, format_segment(segment));
    }
    if (!output.empty())
    {
        append(output, final_separator(regular, thin));
        output += printer.reset();
    }
    return output;
}


size_t
Prompt::length(std::vector<Segment> segments, position pos)
{
    int previous_color = -2;
    size_t total    = 0;
    size_t subtotal = 0;
    size_t separator;
    size_t separator2;

    std::vector<size_t>* length_vector;
    std::vector<std::vector<int>>* id_vector;

    if (pos == position::left)
    {
        separator  = utils::strlen(options.symbols.separator);
        separator2 = utils::strlen(options.symbols.separator2);
        length_vector = &left_lengths_;
        id_vector     = &id_lookup_left_;
    }
    else
    {
        separator  = utils::strlen(options.symbols.rseparator);
        separator2 = utils::strlen(options.symbols.rseparator2);
        length_vector = &right_lengths_;
        id_vector     = &id_lookup_right_;
    }

    length_vector->reserve(segments.size());
    id_vector->resize((int)module::id::__count);

    size_t index = 0;
    for (auto& segment: segments)
    {
        // Build the lookup table for shrink system
        id_vector->at((int)segment.id).push_back(index++);

        if (segment.style.bg == previous_color) {
            subtotal += separator2;
            total += subtotal;
            length_vector->push_back(subtotal);
        }
        else if (previous_color != -2) {
            subtotal += separator;
            total += subtotal;
            length_vector->push_back(subtotal);
        }
        subtotal = 0;
        subtotal += utils::strlen(segment.content);
        subtotal += options.args.padding_left;
        subtotal += options.args.padding_right;
        
        previous_color = segment.style.bg;
    }

    subtotal += previous_color == -1 ? 0 : separator;
    total += subtotal;
    length_vector->push_back(subtotal);

    return total + 1;
    // There's also the top/bot_prefx to keep in mind
    // And also padding_end
}
