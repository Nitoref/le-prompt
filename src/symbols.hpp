#ifndef SYMBOLS_H
#define SYMBOLS_H

#include <string>

struct Symbols
{
    Symbols() = default;

    std::string bash = "\\$";
    std::string fish = "$";
    std::string zsh  = "%#";
    std::string csh  = "%#";
    std::string tcsh = "%#";

    std::string lock     = "\uE0A2"; // ""
    std::string network  = "\uE0A2"; // ""
    std::string cwd_wrap = "\u2026"; // "…"
    
    std::string separator    = "\uE0B0"; // ""
    std::string separator2   = "\uE0B1"; // ""
    std::string rseparator   = "\uE0B2"; // ""
    std::string rseparator2  = "\uE0B3"; // ""
    
    std::string git_branch     = "\uE0A0"; // ""
    std::string git_detached   = "\u27A6"; // "➦"
    std::string git_stash      = "\u2691"; // "⚑"
    std::string git_ahead      = "\u2B06"; // "⬆"
    std::string git_behind     = "\u2B07"; // "⬇"
    std::string git_staged     = "\u2714"; // "✔"
    std::string git_not_staged = "\u270E"; // "✎"
    std::string git_conflicted = "\u273C"; // "✼"
    std::string git_untracked  = "\u2026"; // "…"
};

#endif
