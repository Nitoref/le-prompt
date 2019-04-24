// 858dba background

#include "prompt.hpp"

#include <string>
#include <iostream>


int main(int argc, char const *argv[])
{
    config conf {argc, argv};
    printer::mode(conf._meta.shell);
    Prompt prompt { conf };
    std::cout << prompt.make();
}
