#ifndef COLORUTILS_H
#define COLORUTILS_H

#include "shell_info.hpp"
#include <iostream>
#include <cstring>
#include <string>

#define ESCAPE "\u001b["
#define DEFAULT '9'
#define BG_STD_ '4'
#define FG_STD_ '3'
#define BG_256_ "48;5;"
#define FG_256_ "38;5;"



struct Printer
{
    Printer(Shell shell):
        wrap(shell.wrap),
        unwrap(shell.unwrap)
    {
        wrap_mode(1);
    };
    Printer() = default;
    std::string init;
    std::string stop;
    std::string wrap;
    std::string unwrap;

    void wrap_mode(bool yes)
    {
        init = ESCAPE;
        stop = "";
        if (yes) {
            init.insert(0, wrap);
            stop = unwrap;
        }
    }

    inline std::string bg(int value)
    {
        return init + BG_256_ + std::to_string(value) + 'm' + stop;
    }

    inline std::string fg(int value)
    {
        return init + FG_256_ + std::to_string(value) + 'm' + stop;
    }

    inline std::string reset()
    {
        return init + "0m" + stop;
    }

    inline std::string cup(size_t i)
    {
        return init +(i ? std::to_string(i) : "") + 'G' + stop;
    }

    inline std::string font_style(const char* str)
    {
        static
        std::unordered_map<std::string, int> y =
        {
            {"bold",         1},
            {"faint",        2},
            {"italic",       3},
            {"underline",    4},
            {"blink_slow",   5},
            {"blink_fast",   6},
            {"crossed_out",  9},
            {"framed",      51},
            {"encircled",   52},
            {"overlined",   53}
        };
        if (auto code = y.find(str); code != y.end())
            return init + std::to_string(code->second) + 'm' + stop;
        return "";
    }
};


// namespace ansi
// {


// inline std::string bg(int value)
// {
//     return BG_256_ + std::to_string(value) + 'm';
// }
// inline std::string fg(int value){
//     return FG_256_ + std::to_string(value) + 'm';
// }
// inline std::string reset(){
//     return "0m";
// }

// }


#endif
