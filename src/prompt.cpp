#include "prompt.hpp"

#include <string>
#include <iostream>
#include <algorithm>
#include <functional>
#include <unordered_map>



Prompt::Prompt(config& c):
options(c),
left (c.global.separator,  c.global.separator2,  c.global.padding_left, c.global.padding_right, utils::str_append),
right(c.global.rseparator, c.global.rseparator2, c.global.padding_left, c.global.padding_right, utils::str_prepend),
down (left)
{}


std::string
Prompt::make()
{
    left.preformat();
    right.preformat();
    down.preformat();
    shrink();
    switch (options._meta.shell)
    {
        case config::zsh:
        case config::fish:    
            return print_native();
    }
    return print_emulated();
}


void
Prompt::shrink()
{
    if (left.length + right.length < 0.7 * options._meta.width)
    {
        return;
    }

    for (auto i = priority_list.rbegin(); i != priority_list.rend(); ++i)
    {
        for (auto index: left.id_lookup.at((int)*i))
        {
            left.length -= utils::strlen(left.segments.at(index).content)
            + options.global.padding_left + options.global.padding_right + 1;
        }
        for (auto index: right.id_lookup.at((int)*i))
        {
            right.length -= utils::strlen(right.segments.at(index).content)
            + options.global.padding_left + options.global.padding_right + 1;
        }
        ignored_segments.insert(*i);
        if (left.length + right.length < 0.7 * options._meta.width)
        {
            return;
        }
    }
}

std::string
Prompt::print_native()
{
    std::string output;
    std::string rprompt;
    int align;
    
    Printer::wrap_mode(true);
    
    if (!down.segments.empty() || options.global.force_newline)
    {
        output += options.global.top_prefix;
        output += left.format_without(ignored_segments);

        rprompt = right.format_without(ignored_segments);
        align = options._meta.width - right.actual_length + 1;
        output += Printer::cup(align);
        output += rprompt;
        
        output += Printer::endl;

        output += options.global.bot_prefix;
        output += down.format_without(ignored_segments);
        output += std::string(options.global.padding_end, ' ');
    }
    else
    {
        output += Printer::endl;
        output += left.format_without(ignored_segments);
        output += std::string(options.global.padding_end, ' ');
        output += Printer::endl;
        output += right.format_without(ignored_segments);
    }
    return output;
}


std::string
Prompt::print_emulated()
{
    std::string output;
    std::string rprompt;
    int align;

    Printer::wrap_mode(false);
    
    output += Printer::wrap;

    rprompt = right.format_without(ignored_segments);
    align = options._meta.width - right.actual_length + 1;
    output += Printer::cup(align);
    output += rprompt;

    output += Printer::cup(0);
    output += Printer::unwrap;
    
    Printer::wrap_mode(true);
    
    if (!down.segments.empty() || options.global.force_newline)
    {
        output += options.global.top_prefix;
        output += left.format_without(ignored_segments);
        output += Printer::endl;
        output += options.global.bot_prefix;
        output += down.format_without(ignored_segments);
    }
    else
    {
        output += left.format_without(ignored_segments);
    }
    output += std::string(options.global.padding_end, ' ');
    
    if (options._meta.shell == config::shell_t::csh)
        output += "%{\x1b[D%}";

    return output;
}
