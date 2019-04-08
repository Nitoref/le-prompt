#include "shell_info.hpp"
#include "parse_JSON.hpp"
#include "arguments.hpp"
#include "segments.hpp"
#include "symbols.hpp"
#include "prompt.hpp"
#include "utils.hpp"
#include "theme.hpp"

#include <chrono>
#include <future>
#include <string>
#include <fstream>
#include <iostream>
#include <functional>
#include <unordered_map>


Prompt::Prompt(int argc, char const *argv[])
{
    assert(argc >= 2 && "Thou shall provide $0 and $? as arguments. ($_ and $status for fish)");

    options.shell             =     Shell(argv[1]);
    options.shell.prev_error_ = std::stoi(argv[2]);
    options.shell.width_      = utils::term_width();

    printer = Printer(options.shell);

    if (argc < 4) {
        return;
    }

    try {
        std::ifstream i(argv[3]);
        nlohmann::json j;
        i >> j;
        if (auto k = j.find("args"); k != j.end())
        {
            options.args = k->get<Arguments>();
        }
        if (auto k = j.find("theme"); k != j.end())
        {
            options.theme = k->get<Theme>();
        }
        if (auto k = j.find("symbols"); k != j.end())
        {
            options.symbols = k->get<Symbols>();
        }
        if (auto k = j.find("extension"); k != j.end())
        {
            auto extensions = k->get<std::unordered_map<std::string, segment_constructor_t>>();
            segments_map_.insert(extensions.begin(), extensions.end());
        }
    }
    catch (nlohmann::json::parse_error e) {
        std::cout << "Error parsing config file: Wrong syntax\n" << e.what();
    }
    catch (nlohmann::detail::type_error e) {
        std::cout << "Error parsing config file: Wrong argument\n" << e.what();
    }
    catch (std::system_error e) {
        std::cout << "Error: Invalid config file\n" << e.what();
    }
    catch (...) {
        std::cout << "Error: Invalid config file";
    }
}

segment_constructor_t*
Prompt::get_segment_by_name(std::string str)
{
    if (auto s = segments_map_.find(str); s != segments_map_.end())
    {
        return &s->second;
    }
    return nullptr;
}

void
Prompt::make_segments()
{
    std::vector<std::future<Segment>> left_futures;
    std::vector<std::future<Segment>> right_futures;
    
    left_futures.reserve(options.args.left_segments.size());
    right_futures.reserve(options.args.left_segments.size());

    for (auto str: options.args.left_segments)
    {
        if (auto fun = get_segment_by_name(str))
        {
            left_futures.push_back( std::async( 
                std::launch::async, [=](){ return (*fun)(options);}
            ));
        }
    }

    for (auto str: options.args.right_segments)
    {
        if (auto fun = get_segment_by_name(str))
        {
            right_futures.push_back( std::async(
                std::launch::async, [=](){ return (*fun)(options);})
            );
        }
    }

    left_segments_.reserve(left_futures.size());
    right_segments_.reserve(left_futures.size());

    for (auto& future: left_futures) {
        auto status = future.wait_for(std::chrono::seconds(1));
        if (status == std::future_status::timeout)
        {
            left_segments_.push_back(Segment{"408", {5, 12}});
        }
        if (auto segment = future.get())
        {
            left_segments_.push_back(segment);
        }
    }
    for (auto& future: right_futures) {
        auto status = future.wait_for(std::chrono::seconds(1)) ;
        if (status== std::future_status::timeout)
        {
            right_segments_.push_back(Segment{"408", {5, 12}});
        }
        if (auto segment = future.get())
        {
            right_segments_.push_back(segment);
        }
    }
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

    for (auto &segment : segments)
    {
        add(output, make_separator(segment, regular, thin));
        add(output, format_segment(segment));
    }
    if (!output.empty())
    {
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
    for (auto& segment: segments)
    {
        if (segment.style.bg == color)
        {
            length += utils::string::length(options.symbols.separator);
        } 
        else
        {
            length += utils::string::length(options.symbols.separator_thin);
        }
        color = segment.style.bg;
        length += 2 + utils::string::length(segment.content);
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
