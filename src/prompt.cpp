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
left (options.symbols.separator,  options.symbols.separator2,  options.args.padding_left, options.args.padding_right, utils::str_append),
right(options.symbols.rseparator, options.symbols.rseparator2, options.args.padding_left, options.args.padding_right, utils::str_prepend),
down (left)
{}


std::string
Prompt::make()
{
    left.preformat();
    right.preformat();
    down.preformat();
    shrink();
    switch (options.shell.id)
    {
        case Shell::Type::zsh:
        case Shell::Type::fish:    
            return print_native();
    }
    return print_emulated();
}


void
Prompt::shrink()
{
    if (left.length + right.length < 0.7 * options.shell.width)
    {
        return;
    }

    for (auto i = priority_list.rbegin(); i != priority_list.rend(); ++i)
    {
        for (auto index: left.id_lookup.at((int)*i))
        {
            left.length -= utils::strlen(left.segments.at(index).content)
            + options.args.padding_left + options.args.padding_right + 1;
        }
        for (auto index: right.id_lookup.at((int)*i))
        {
            right.length -= utils::strlen(right.segments.at(index).content)
            + options.args.padding_left + options.args.padding_right + 1;
        }
        ignored_segments.insert(*i);
        if (left.length + right.length < 0.7 * options.shell.width)
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
    
    if (!down.segments.empty() || options.args.force_newline)
    {
        output += options.symbols.top_prefix;
        output += left.format_without(ignored_segments);

        rprompt = right.format_without(ignored_segments);
        align = options.shell.width - right.actual_length + 1;
        output += Printer::cup(align);
        output += rprompt;
        
        output += Printer::endl;

        output += options.symbols.bot_prefix;
        output += down.format_without(ignored_segments);
        output += std::string(options.args.padding_end, ' ');
    }
    else
    {
        output += Printer::endl;
        output += left.format_without(ignored_segments);
        output += std::string(options.args.padding_end, ' ');
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
    align = options.shell.width - right.actual_length + 1;
    output += Printer::cup(align);
    output += rprompt;

    output += Printer::cup(0);
    output += Printer::unwrap;
    
    Printer::wrap_mode(true);
    
    if (!down.segments.empty() || options.args.force_newline)
    {
        output += options.symbols.top_prefix;
        output += left.format_without(ignored_segments);
        output += Printer::endl;
        output += options.symbols.bot_prefix;
        output += down.format_without(ignored_segments);
    }
    else
    {
        output += left.format_without(ignored_segments);
    }
    output += std::string(options.args.padding_end, ' ');
    
    if (options.shell.id == Shell::Type::csh)
        output += "%{\x1b[D%}";

    return output;
}
