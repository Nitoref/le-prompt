#ifndef PROMPT_CONFIG_H
#define PROMPT_CONFIG_H

#include "arguments.hpp"
#include "symbols.hpp"
#include "theme.hpp"
#include "shell.hpp"


struct Config
{
    Arguments args;
    Symbols   symbols;
    Theme     theme;
    Shell     shell;
};


#endif
