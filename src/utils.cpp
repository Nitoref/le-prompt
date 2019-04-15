#include <stdexcept>
#include <memory>
#include <iostream>
#include <string>
#include <cstring>
#include <array>
#include <sys/ioctl.h>
#include <stdio.h>
#include "utils.hpp"



namespace utils
{


std::vector<std::string>
exec(const std::string& cmd)
{
    using pipe = std::unique_ptr<FILE,decltype(&pclose)>;    
    std::vector<std::string> out;
    std::array<char, 1024> buff;

    if (pipe p(popen(cmd.data(), "r"), pclose); p)
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


size_t
term_width ()
{
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    return w.ws_col;
}



namespace string
{


void prepend(std::string& where, std::string what)
{
    where.insert(0, what);
}


void append(std::string& where, std::string what)
{
    where.append(what);
}


void
replace_all(std::string& where, std::string what, std::string with)
{
    size_t from = 0;
    while((from = where.find(what, from)) != std::string::npos)
    {
        where.replace(from, what.length(), with);
        from += with.length();
    }
}

void
replace_all(std::string& where, char what, std::string with)
{
    size_t from = 0;
    while((from = where.find(what, from)) != std::string::npos)
    {
        where.replace(from, 1, with);
        from += with.length();
    }
}


size_t
rnfind (std::string& s, char c, size_t n)
{
    if (n != 0  && !s.empty())
        for (int i = s.length() - 1; i >= 0; --i)
            if (s.at(i) == c)
                if (--n == 0)
                    return i;
    return std::string::npos;
}


size_t length(std::string s) {
    return length(s.c_str());
}


// Props to http://www.daemonology.net/blog/2008-06-05-faster-utf8-strlen.html
#define ONEMASK ((size_t)(-1) / 0xFF)
size_t 
length(const char * s_)
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


}
