#ifndef SYMBOLS_H
#define SYMBOLS_H

struct Symbols
{
    Symbols() = default;
    string lock             = "\uE0A2"; // ""
    string network          = "\uE0A2"; // ""
    string separator        = "\uE0B4"; // ""
    string r_separator      = "\uE0B4"; // ""
    string separator_thin   = "\uE0B5"; // ""
    string r_separator_thin = "\uE0B5"; // ""
    string git_branch       = "\uE0A0"; // ""
    string git_detached     = "\u27A6"; // "➦"
    string git_ahead        = "\u2B06"; // "⬆"
    string git_behind       = "\u2B07"; // "⬇"
    string git_staged       = "\u2714"; // "✔"
    string git_not_staged   = "\u270E"; // "✎"
    string git_conflicted   = "\u273C"; // "✼"
    string git_untracked    = "\u2026"; // "…"
};

#endif
