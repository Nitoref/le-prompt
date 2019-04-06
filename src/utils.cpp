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

int term_width ()
{
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    return w.ws_col;
}


std::list<std::string>
exec(const std::string& cmd)
{
    std::array<char, 1024> buffer;
    std::list<std::string> result;
    std::unique_ptr<FILE,decltype(&pclose)> pipe(popen(cmd.data(), "r"), pclose);
    if (pipe)
    {
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
        {
            result.emplace_back(buffer.data());
        }
    }
    return result;
}


namespace string
{

std::string
safe(const char* s)
{
    if (s == NULL)
        return "";
    return s;
}
void
replace_all(std::string& in, const std::string& from, const std::string& to)
{
    size_t cursor = 0;
    while((cursor = in.find(from, cursor)) != std::string::npos)
    {
        in.replace(cursor, from.length(), to);
        cursor += to.length();
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


// Props to http://www.daemonology.net/blog/2008-06-05-faster-utf8-strlen.html
#define ONEMASK ((size_t)(-1) / 0xFF)
size_t 
length(const char * s_)
{
    const char * s;
    size_t count = 0;
    size_t u;
    unsigned char b;

    /* Handle any initial misaligned bytes. */
    for (s = s_; (uintptr_t)(s) & (sizeof(size_t) - 1); s++) {
        b = *s;

        /* Exit if we hit a zero byte. */
        if (b == '\0')
            goto done;

        /* Is this byte NOT the first byte of a character? */
        count += (b >> 7) & ((~b) >> 6);
    }

    /* Handle complete blocks. */
    for (; ; s += sizeof(size_t)) {
        /* Prefetch 256 bytes ahead. */
        __builtin_prefetch(&s[256], 0, 0);

        /* Grab 4 or 8 bytes of UTF-8 data. */
        u = *(size_t *)(s);

        /* Exit the loop if there are any zero bytes. */
        if ((u - ONEMASK) & (~u) & (ONEMASK * 0x80))
            break;

        /* Count bytes which are NOT the first byte of a character. */
        u = ((u & (ONEMASK * 0x80)) >> 7) & ((~u) >> 6);
        count += (u * ONEMASK) >> ((sizeof(size_t) - 1) * 8);
    }

    /* Take care of any left-over bytes. */
    for (; ; s++) {
        b = *s;

        /* Exit if we hit a zero byte. */
        if (b == '\0')
            break;

        /* Is this byte NOT the first byte of a character? */
        count += (b >> 7) & ((~b) >> 6);
    }

    done:
    return ((s - s_) - count);
}

size_t length(std::string s) {
    return length(s.c_str());
}



}


}