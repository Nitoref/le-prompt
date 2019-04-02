#ifndef COLORUTILS_H
#define COLORUTILS_H

#include "theme.hpp"
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

template<typename ...Args>
void fmt(Args&&... args) {
    std::string s{args...};
    // s += args;
    // (std::cout << ... << args);
}

struct ColorPrinter
{
    ColorPrinter(Shell shell):
        escape_(shell.escape_),
        epacse_(shell.epacse_)
    {};
    const char* escape_;
    const char* epacse_;

    inline void set_bg(int value){
        printf("%s%s%d%s",escape_, BG_256_, value, epacse_);
    }

    inline void set_fg(int value){
        printf("%s%s%d%s",escape_, FG_256_, value, epacse_);
    }

    inline void reset_bg(){
        printf("%s%c%d%s",escape_, BG_STD_, DEFAULT, epacse_);
    }

    inline void reset_fg(){
        printf("%s%c%d%s",escape_, FG_STD_, DEFAULT, epacse_);
    }

    inline void reset_style(){
        printf("%s%c%s",escape_, '0', epacse_);
    }

    inline char* bg_color(int value)
    {
        char* out;
        asprintf(&out, "%s%s%d%s", escape_, BG_256_, value, epacse_);
        return out;
    }

    inline char* fg_color(int value){
        char* out;
        asprintf(&out, "%s%s%d%s", escape_, FG_256_, value, epacse_);
        return out;
    }

    inline char* reset(){
        char* out;
        asprintf(&out, "%s%c%s", escape_, '0', epacse_);
        return out;
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
            printf("%s%dm%s",escape_, y[str], epacse_);
    }
};

#endif
