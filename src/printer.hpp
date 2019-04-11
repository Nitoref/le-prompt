#ifndef COLORUTILS_H
#define COLORUTILS_H

#include "shell.hpp"
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
    Printer(Shell::Type id)
    {
        switch (id)
        {
        case Shell::bash:
            wrap       = "\\[";
            unwrap     = "\\]";
            break;

        case Shell::zsh:
        case Shell::csh:
        case Shell::tcsh:
            wrap       = "%{";
            unwrap     = "%}";
            break;

        default:
            wrap       = "";
            unwrap     = "";
            break;
        }
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

    inline std::string font(const char* str)
    {
        static
        std::unordered_map<std::string, int> y =
        {
            {"bold",      1},
            {"faint",     2},
            {"italic",    3},
            {"underline", 4},
            {"blink",     5},
            {"rblink",    6},
            {"reversed",  7},
            {"conceal",   8},
            {"crossed",   9},
        };
        if (auto code = y.find(str); code != y.end())
            return init + std::to_string(code->second) + 'm' + stop;
        return "";
    }
};





#endif
