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


std::string
SubPrompt::format_without(std::unordered_set<module::id>& ignored)
{
    std::string output;
    output.reserve(20 * segments.size());
    for (auto &segment : segments)
    {
        auto found = ignored.find(segment.id);
        if (found != ignored.end())
            continue;
        append(output, make_separator(segment));
        append(output, format_segment(segment));
    }
    if (!output.empty())
    {
        append(output, final_separator());
        output += Printer::reset();
    }
    return output;
}


std::string
SubPrompt::format_segment(Segment s) 
{
    std::string output;
    output.reserve(20);
    output += Printer::bg(s.style.bg);
    output += Printer::fg(s.style.fg);
    output += std::string(padding_left, ' ');
    output += s.content;
    output += std::string(padding_right, ' ');

    actual_length += padding_left;
    actual_length += padding_right;
    actual_length += utils::strlen(s.content);
    return output;
}


std::string
SubPrompt::make_separator(Segment s)
{
    std::string output;
    output.reserve(20); // maybe ?
    if (s.style.bg == prev_color)
    {
        output += Printer::fg(160); //options.theme.separator.fg
        output += separator2;
        actual_length += separator2_length;
    }
    else
    if (prev_color == -1)
    {
        output += Printer::fg(s.style.bg);
        output += Printer::bg(prev_color);
        output += Printer::font("reversed");
        output += separator;
        output += Printer::reset();
        actual_length += separator_length;
    }
    else
    if (prev_color != -2)
    {
        output += Printer::fg(prev_color);
        output += Printer::bg(s.style.bg);
        output += separator;
        actual_length += separator_length;
    }
    prev_color = s.style.bg;
    return output;
}


std::string
SubPrompt::final_separator()
{
    std::string output;
    output += Printer::reset();
    output += Printer::fg(prev_color);
    if (prev_color != -1) 
    {
        output += separator;
        actual_length += separator_length;
    }
    prev_color = -2;
    return output;
}


void
SubPrompt::preformat()
{
    prev_color = -2;
    size_t subtotal = 0;

    id_lookup.resize((int)module::id::__count);

    size_t i = 0;
    for (auto& segment: segments)
    {
        id_lookup.at((int)segment.id).push_back(i++);

        if (segment.style.bg == prev_color)
        {
            subtotal += separator2_length;
            length   += subtotal;
        }
        else if (prev_color != -2)
        {
            subtotal += separator_length;
            length   += subtotal;
        }
        subtotal = 0;
        subtotal += utils::strlen(segment.content);
        subtotal += padding_left;
        subtotal += padding_right;
        
        prev_color = segment.style.bg;
    }
    if (prev_color != - 1)
    {
        subtotal += separator_length;
    }
    length += subtotal;
    // lengths.push_back(subtotal);

    length += 1;
    prev_color = -2;
}