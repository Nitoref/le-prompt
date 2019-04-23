#include <stdexcept>
#include <memory>
#include <iostream>
#include <string>
#include <cstring>
#include <array>
#include <stdio.h>
#include "utils.hpp"

#ifdef _WIN32
#   include <windows.h>
#else
#   include <sys/ioctl.h>
#endif


namespace utils
{

size_t
term_width ()
{
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    size_t columns, rows;
    GetConsoleScreenBufferInfo(
        GetStdHandle(STD_OUTPUT_HANDLE), &csbi
    );
    return csbi.srWindow.Right  - csbi.srWindow.Left + 1;
#else
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    return w.ws_col;
#endif
}



std::vector<std::string>
exec(const std::string& cmd)
{
    using pipe = std::unique_ptr<FILE,decltype(&pclose)>;    
    std::vector<std::string> out;
    std::array<char, 1024> buff;

#ifdef _WIN32
    if (pipe p(_popen(cmd.data(), "r"), pclose); p)
#else
    if (pipe p(popen(cmd.data(), "r"), pclose); p)
#endif
    {
        while (fgets(buff.data(), buff.size(), p.get()) != nullptr)
        {
            out.emplace_back(buff.data());
            if (out.back().back() == '\n')
            {
                out.back().pop_back();
            }
        }
    }
    return out;
}



void
strrepl(std::string& where, std::string what, std::string with)
{
    size_t from = 0;
    while((from = where.find(what, from)) != std::string::npos)
    {
        where.replace(from, what.length(), with);
        from += with.length();
    }
}


void
str_prepend(std::string& where, std::string what)
{
    where.insert(0, what);
}

void
str_append(std::string& where, std::string what)
{
    where.append(what);
}


size_t
strlen(std::string s)
{
    return strlen(s.c_str());
}

// Props to http://www.daemonology.net/blog/2008-06-05-faster-utf8-strlen.html
#define ONEMASK ((size_t)(-1) / 0xFF)
size_t
strlen(const char * s_)
{
    const char * s;
    size_t count = 0;
    size_t u;
    unsigned char b;

    for (s = s_; (uintptr_t)(s) & (sizeof(size_t) - 1); s++)
    {
        b = *s;
        if (b == '\0')
            goto done;

        count += (b >> 7) & ((~b) >> 6);
    }
    for (; ; s += sizeof(size_t))
    {
        __builtin_prefetch(&s[256], 0, 0);
        u = *(size_t *)(s);
        if ((u - ONEMASK) & (~u) & (ONEMASK * 0x80)) {
            break;
        }
        u = ((u & (ONEMASK * 0x80)) >> 7) & ((~u) >> 6);
        count += (u * ONEMASK) >> ((sizeof(size_t) - 1) * 8);
    }

    for (; ; s++)
    {
        b = *s;
        if (b == '\0') {
            break;
        }
        count += (b >> 7) & ((~b) >> 6);
    }
done:
    return ((s - s_) - count);
}


}
