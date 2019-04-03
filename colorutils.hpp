#ifndef COLORUTILS_H
#define COLORUTILS_H

#include "string.hpp"
#include "shell_info.hpp"
#include <iostream>
#include <cstring>

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
    string escape_;
    string epacse_;

    inline void set_bg(int value){
        print(escape_, BG_256_, value, epacse_);
    }

    inline void set_fg(int value){
        print(escape_, FG_256_, value, epacse_);
    }

    inline void reset_bg(){
        print(escape_, BG_STD_, DEFAULT, epacse_);
    }

    inline void reset_fg(){
        print(escape_, FG_STD_, DEFAULT, epacse_);
    }

    inline void reset_style(){
        print(escape_, '0', epacse_);
    }

    inline string bg_color(int value)
    {
        return string {escape_ + BG_256_ + std::to_string(value) + epacse_};
    }

    inline string fg_color(int value){
        return string {escape_ + FG_256_ + std::to_string(value) + epacse_};
    }

    inline string reset(){
        return string {escape_ + '0' + epacse_};
    }


    inline void set_font_style(const char* str){
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
        if (y.count(str))
            print(escape_, y[str], epacse_);
    }
};

#endif
