// 858dba background

#include "prompt.hpp"

#include <ios>
#include <string>
#include <iostream>


int main(int argc, char const *argv[])
{
    std::ios_base::sync_with_stdio(false);

    config conf {argc, argv};
    
    printer::mode(conf._meta.shell);
    
    Prompt prompt { conf };

    std::cout << prompt.make();
}
