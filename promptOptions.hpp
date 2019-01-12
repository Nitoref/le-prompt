#ifndef PROMPT_H
#define PROMPT_H

#include "arguments.hpp"
#include "theme.hpp"

struct PromptOpt{
    PromptOpt() = default;
    PromptOpt(
        Arguments args,
        Symbols   symbols,
        Theme     theme,
        Shell     shell
    ):
        args(args),
        symbols(symbols),
        theme(theme),
        shell(shell)
    {}
    Arguments args;
    Symbols   symbols;
    Theme     theme;
    Shell     shell;
};


#endif
