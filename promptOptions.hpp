#ifndef PROMPT_H
#define PROMPT_H

#include "arguments.hpp"
#include "theme.hpp"

struct PromptOpt{
    PromptOpt(const Arguments *args, const ShellInfo *shell, const Symbols *symbols, const Theme *theme)
    {
        this->shell   = shell;
        this->symbols = symbols;
        this->theme   = theme;
        this->args    = args;
    }
    const Arguments    *args;
    const ShellInfo    *shell;
    const Symbols      *symbols;
    const Theme        *theme;
};


#endif
