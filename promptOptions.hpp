#ifndef PROMPT_H
#define PROMPT_H

#include "arguments.hpp"
#include "theme.hpp"

struct PromptOpt{
    PromptOpt(
        const Arguments &args,
        const Shell &shell,
        const Symbols   &symbols,
        const Theme     &theme
    ):
        shell(shell),
        symbols(symbols),
        theme(theme),
        args(args)
    {}
    const Arguments &args;
    const Shell     &shell;
    const Symbols   &symbols;
    const Theme     &theme;
};


#endif
