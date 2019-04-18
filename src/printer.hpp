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
    Printer() = delete;

    static inline std::string init;
    static inline std::string stop;
    static inline std::string wrap;
    static inline std::string unwrap;
    static inline std::string endl;
    
    static void mode(Shell::Type id)
    {
        switch (id)
        {
        case Shell::bash:
            wrap   = "\\[";
            unwrap = "\\]";
            endl   = "\n";
            break;

        case Shell::csh:
            wrap   = "%{";
            unwrap = "%}";
            endl   = " \\n";
            break;

        case Shell::zsh:
            wrap   = "%{";
            unwrap = "%}";
            endl   = "\n";
            break;
        
        default:
            endl   = "\n";
            break;
        }
    };

    static void wrap_mode(bool yes)
    {
        init = ESCAPE;
        stop = "";
        if (yes) {
            init.insert(0, wrap);
            stop = unwrap;
        }
    }

    static inline std::string bg(int value)
    {
        std::string s(init);
        if (value < 0) {
            s += BG_STD_;
            s += '9';
        } else {
            s += BG_256_;
            s += std::to_string(value);
        }
        s += 'm';
        s += stop;
        return s;
    }

    static inline std::string fg(int value)
    {
        std::string s(init);
        if (value < 0) {
            s += FG_STD_;
            s += '9';
        } else {
            s += FG_256_;
            s += std::to_string(value);
        }
        s += 'm';
        s += stop;
        return s;
    }

    static inline std::string reset()
    {
        return init + "0m" + stop;
    }

    static inline std::string cup(size_t i)
    {
        return init +(i ? std::to_string(i) : "") + 'G' + stop;
    }

    static inline std::string font(const char* str)
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
