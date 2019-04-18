#ifndef SYMBOLS_H
#define SYMBOLS_H

#include <string>


struct Symbols
{
    Symbols() = default;

    std::string separator   = ""; // "\uE0B0"
    std::string separator2  = ""; // "\uE0B1"
    std::string rseparator  = ""; // "\uE0B2"
    std::string rseparator2 = ""; // "\uE0B3"
    
    std::string top_prefix = "";
    std::string bot_prefix = "";
    
    // std::string separator   = ""; // "\uE0B4"
    // std::string separator2  = ""; // "\uE0B5"
    // std::string rseparator  = ""; // "\uE0B6"
    // std::string rseparator2 = ""; // "\uE0B7"

    // std::string separator   = "◤"; // "\u25E4"
    // std::string separator2  = "▸";  // "\u25B8"
    // std::string rseparator  = "◥"; // "\u25E5"
    // std::string rseparator2 = "◂";  // "\u25C2"

    std::string home     = "~";
    std::string prompt   = ">";
    std::string root     = "#";
    std::string host     = "@";
    std::string jobs     = "…";
    std::string node     = "⬢";
    std::string readonly = " ⃠"; // "\u20E0"
    std::string dir_wrap = "…";  // "\u2026"
    
    // std::string prompt   = "❯";
    // std::string host     = "@";
    // std::string root     = " "; // "\uF09C"
    // std::string jobs     = "";  // "\uF013"
    // std::string readonly = " "; // "\uF023"
    // std::string dir_wrap = "…";  // "\u2026"
    
    std::string git_branch   = "";  // ""
    std::string git_dirty    = "✳"; //
    std::string git_hash     = "#"; // ""
    std::string git_tag      = "&"; // ""
    std::string git_stash    = "✳"; // "⚑"
    std::string git_ahead    = "↑"; // ""
    std::string git_behind   = "↓"; // ""
    std::string git_staged   = "+"; // ""
    std::string git_nstaged  = "!"; // "✎"
    std::string git_conflicted = "×"; // "×"
    std::string git_untracked  = "?"; // "…"
};

#endif
