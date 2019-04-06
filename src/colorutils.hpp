#ifndef COLORUTILS_H
#define COLORUTILS_H

#include "shell_info.hpp"
#include <iostream>
#include <cstring>
#include <string>

#define DEFAULT '9'
#define BG_STD_ '4'
#define FG_STD_ '3'
#define BG_256_ "48;5;"
#define FG_256_ "38;5;"


template<typename ...Args>
void print(Args&&... args) {
    (std::cout << ... << args);
}

struct ColorPrinter
{
    ColorPrinter(Shell shell):
        escape_(shell.escape_),
        epacse_(shell.epacse_)
    {};
    std::string escape_;
    std::string epacse_;

    inline std::string bg(int value)
    {
        return escape_ + BG_256_ + std::to_string(value) + epacse_;
    }

    inline std::string fg(int value){
        return escape_ + FG_256_ + std::to_string(value) + epacse_;
    }

    inline std::string reset(){
        return escape_ + '0' + epacse_;
    }

    inline std::string font_style(const char* str){
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
            return escape_ + std::to_string(code->second) + epacse_;
        return "";
    }
};

#endif
