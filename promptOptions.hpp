#ifndef PROMPT_H
#define PROMPT_H

#include "promptOptions.hpp"
#include <iostream>

#include "arguments.hpp"
#include "theme.hpp"

struct PromptOpt
{
    Arguments args;
    Symbols   symbols;
    Theme     theme;
    Shell     shell;

    PromptOpt(char const *argv[])
    {
        try {
            auto config = cpptoml::parse_file(argv[4]);
            args        = Arguments(config);
            symbols     = Symbols(config);
            theme       = Theme(config);
        }
        catch(cpptoml::parse_exception& ex) {
            std::cerr << "Error parsing config file :\n\t" << ex.what() << std::endl;
        }
        shell          =     Shell(argv[1]);
        args.prev_error = std::stoi(argv[2]);
        args.term_width = std::stoi(argv[3]);
    }
};

#endif
