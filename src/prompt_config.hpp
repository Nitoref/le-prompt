#ifndef PROMPT_H
#define PROMPT_H

#include <iostream>
#include <fstream>

#include "parse_JSON.hpp"
#include "arguments.hpp"
#include "theme.hpp"
#include "symbols.hpp"
#include "shell_info.hpp"

struct PromptConfig
{
    Arguments args;
    Symbols   symbols;
    Theme     theme;
    Shell     shell;

    PromptConfig(char const *argv[])
    {
        std::ifstream i(argv[4]);
        nlohmann::json j;
        i >> j;

        if (auto k = j.find("args"); k != j.end())
            args = k->get<Arguments>();
        if (auto k = j.find("theme"); k != j.end())
            theme = k->get<Theme>();
        if (auto k = j.find("symbols"); k != j.end())
            symbols = k->get<Symbols>();

        shell           =     Shell(argv[1]); 
        args.prev_error = std::stoi(argv[2]); 
        args.term_width = std::stoi(argv[3]); 
    }
};

#endif
