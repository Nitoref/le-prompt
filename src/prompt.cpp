#include "prompt.hpp"
#include "modules.hpp"

#include <chrono>
#include <future>
#include <string>
#include <iostream>
#include <algorithm>
#include <functional>
#include <unordered_map>


std::vector<std::future<Segment>>
spawn(std::vector<std::string>& segments, config& config)
{
    std::vector<std::future<Segment>> futures;
    futures.reserve(segments.size());
    for (auto str: segments) {
        if (auto fun = constructor::get(str)) {
            futures.push_back( std::async( 
                std::launch::async, [=, &config](){
                    return (*fun)(config);
                }
            ));
        }
    }
    return futures;
}

std::vector<Segment>
join(std::vector<std::future<Segment>>& futures)
{
    std::vector<Segment> segments;
    segments.reserve(futures.size());
    
    for (auto& future: futures) {
        if (auto segment = future.get()) {
            segments.emplace_back(segment);
        }
    }
    return segments;
}


Prompt::Prompt(config& c):
conf(c),
left (c.global.separator , c.global.separator2 , c.global.padding_left, c.global.padding_right, utils::str_append),
right(c.global.rseparator, c.global.rseparator2, c.global.padding_left, c.global.padding_right, utils::str_prepend),
down (left)
{
    auto left_futures  = spawn(conf.segments.left , conf);
    auto right_futures = spawn(conf.segments.right, conf);
    auto down_futures  = spawn(conf.segments.down , conf);

    left.segments  = join(left_futures);
    right.segments = join(right_futures);
    down.segments  = join(down_futures);
}


std::string
Prompt::make()
{
    left.preformat();
    right.preformat();
    down.preformat();
    shrink();

    switch (conf._meta.shell)
    {
        case shell_t::zsh:
        case shell_t::fish:
            return print_native();
        default:
            return print_emulated();
        break;
    }
}


void
Prompt::shrink()
{
    if (left.length + right.length < conf.global.width_limit * conf._meta.width)
    {
        return;
    }

    for (auto i = priority_list.rbegin(); i != priority_list.rend(); ++i)
    {
        if (auto index = left.id_lookup.at((int)*i))
        {
            left.length -= left.segments.at(*index).length()
            + conf.global.padding_left + conf.global.padding_right + 1;
        }
        if (auto index = right.id_lookup.at((int)*i))
        {
            right.length -= right.segments.at(*index).length()
            + conf.global.padding_left + conf.global.padding_right + 1;
        }
        ignored_segments.insert(*i);
        if (left.length + right.length < conf.global.width_limit * conf._meta.width)
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
    
    printer::wrap_mode(true);
    
    if (!down.segments.empty() || conf.global.force_newline)
    {
        output += conf.global.top_prefix;
        output += left.format_without(ignored_segments);

        rprompt = right.format_without(ignored_segments);
        align = conf._meta.width - right.actual_length + 1;
        output += printer::cup(align);
        output += rprompt;
        
        output += printer::endl;

        output += conf.global.bot_prefix;
        output += down.format_without(ignored_segments);
        output += std::string(conf.global.padding_end, ' ');
    }
    else
    {
        output += printer::endl;
        output += left.format_without(ignored_segments);
        output += std::string(conf.global.padding_end, ' ');
        output += printer::endl;
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

    printer::wrap_mode(false);
    
    output += printer::wrap;

    rprompt = right.format_without(ignored_segments);
    align = conf._meta.width - right.actual_length + 1;
    output += printer::cup(align);
    output += rprompt;

    output += printer::cup(0);
    output += printer::unwrap;
    
    printer::wrap_mode(true);
    
    if (!down.segments.empty() || conf.global.force_newline)
    {
        output += conf.global.top_prefix;
        output += left.format_without(ignored_segments);
        output += printer::endl;
        output += conf.global.bot_prefix;
        output += down.format_without(ignored_segments);
    }
    else
    {
        output += left.format_without(ignored_segments);
    }
    output += std::string(conf.global.padding_end, ' ');
    
    if (conf._meta.shell == shell_t::csh)
        output += "%{\x1b[D%}";

    return output;
}
