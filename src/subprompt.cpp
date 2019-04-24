#include "subprompt.hpp"



std::string
SubPrompt::format_without(std::unordered_set<segment::id>& ignored)
{
    std::string output;
    output.reserve(20 * segments.size());
    for (auto &segment : segments)
    {
        auto found = ignored.find(segment.id());
        if (found != ignored.end())
            continue;
        append(output, make_separator(segment));
        append(output, format_segment(segment));
    }
    if (!output.empty())
    {
        append(output, final_separator());
        output += printer::reset();
    }
    return output;
}


std::string
SubPrompt::format_segment(Segment s) 
{
    std::string output;
    output.reserve(20);
    output += printer::fg(s.theme().fg);
    output += printer::bg(s.theme().bg);
    output += std::string(padding_left, ' ');
    output += s.content();
    output += std::string(padding_right, ' ');

    actual_length += padding_left;
    actual_length += padding_right;
    actual_length += s.length();
    return output;
}


std::string
SubPrompt::make_separator(Segment s)
{
    std::string output;
    output.reserve(20); // maybe ?
    if (s.theme().bg == prev_color)
    {
        output += printer::fg(245); //options.theme.separator.fg
        output += separator2;
        actual_length += separator2_length;
    }
    else
    if (prev_color == -1)
    {
        output += printer::fg(s.theme().bg);
        output += printer::bg(prev_color);
        output += printer::font("reversed");
        output += separator;
        output += printer::reset();
        actual_length += separator_length;
    }
    else
    if (prev_color != -2)
    {
        output += printer::fg(prev_color);
        output += printer::bg(s.theme().bg);
        output += separator;
        actual_length += separator_length;
    }
    prev_color = s.theme().bg;
    return output;
}


std::string
SubPrompt::final_separator()
{
    std::string output;
    output += printer::reset();
    output += printer::fg(prev_color);
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

    id_lookup.resize((int)segment::id::__count);

    size_t i = 0;
    for (auto& segment: segments)
    {
        id_lookup.at((int)segment.id()) = i++;

        if (segment.theme().bg == prev_color)
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
        subtotal += segment.length();
        subtotal += padding_left;
        subtotal += padding_right;
        
        prev_color = segment.theme().bg;
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
