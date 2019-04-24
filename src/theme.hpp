#ifndef THEME_HPP
#define THEME_HPP


#include <vector>
#include <string>


struct Theme
{
    int   fg = -1;
    int   bg = -1;
    std::vector<std::string> font;
};


#endif
