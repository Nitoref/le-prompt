#ifndef PROMPT_CONFIG_H
#define PROMPT_CONFIG_H

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
};

#endif
