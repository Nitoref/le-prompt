#ifndef PROMPT_H
#define PROMPT_H

#include <iostream>
#include <fstream>

#include "parse_JSON.hpp"
#include "arguments.hpp"
#include "theme.hpp"
#include "symbols.hpp"
#include "shell_info.hpp"
#include "utils.hpp"


struct PromptConfig
{
    Arguments args;
    Symbols   symbols;
    Theme     theme;
    Shell     shell;

    PromptConfig(char const *argv[])
    {
        std::ifstream i(argv[3]);
        nlohmann::json j;
        i >> j;

        if (auto k = j.find("args"); k != j.end())
            args = k->get<Arguments>();
        if (auto k = j.find("theme"); k != j.end())
            theme = k->get<Theme>();
        if (auto k = j.find("symbols"); k != j.end())
            symbols = k->get<Symbols>();

        shell             =     Shell(argv[1]);
        shell.prev_error_ = std::stoi(argv[2]);
        shell.width_      = utils::term_width();
    }
};

#endif
