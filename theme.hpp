#ifndef THEME_H
#define THEME_H

#include "cpptoml.hpp"


struct ShellInfo;
const extern ShellInfo Bash;
const extern ShellInfo Zsh;
const extern ShellInfo Bare;


struct ShellInfo
{
    ShellInfo() = default;
    const char* colorTemplate;
    const char* rootIndicator;
    const char* escapedBackslash;
    const char* escapedBacktick;
    const char* escapedDollar;
};

struct Symbols
{
    Symbols() = default;
    Symbols(std::shared_ptr<cpptoml::table> syms);
    const char* Lock          = "\uE0A2"; // ""
    const char* Network       = "\uE0A2"; // ""
    const char* Separator     = "\uE0B4"; // ""
    const char* SeparatorThin = "\uE0B5"; // ""
    const char* GitBranch     = "\uE0A0"; // ""  //  "⇢"
    const char* GitDetached   = "\u27A6"; // "➦"  //  "⇤"
    const char* GitAhead      = "\u2B06"; // "⬆"
    const char* GitBehind     = "\u2B07"; // "⬇"
    const char* GitStaged     = "\u2714"; // "✔"
    const char* GitNotStaged  = "\u270E"; // "✎"
    const char* GitConflicted = "\u273C"; // "✼"
    const char* GitUntracked  = "\u2026"; // "…"
};


struct Style
{
    Style() = default;
    Style(int fg, int bg):fg(fg),bg(bg){};
    int   fg;
    int   bg;
};


struct Theme
{
    Theme() = default;
    Theme(std::shared_ptr<cpptoml::table> conf);
    Style Separator     = { 15  , 0 } ;
    Style Username      = { 250 , 240};
    Style UsernameRoot  = { 250 , 124};
    Style Hostname      = { 250 , 238};
    Style Home          = { 15  , 31};
    Style Path          = { 250 , 237};
    Style Cwd           = { 254 , 237};
    Style Readonly      = { 254 , 124};
    Style Ssh           = { 254 , 166};
    Style DockerMachine = { 177 , 55};
    Style KubeCluster   = { 117 , 26};
    Style KubeNamespace = { 170 , 17};
    Style DotEnv        = { 15  , 55};
    Style Aws           = { 15  , 22};
    Style RepoClean     = { 0   , 148};
    Style RepoDirty     = { 15  , 161};
    Style Jobs          = { 39  , 238};
    Style CmdPassed     = { 15  , 236};
    Style CmdFailed     = { 15  , 161};
    Style SvnChanges    = { 22  , 148};
    Style GitAhead      = { 250 , 240};
    Style GitBehind     = { 250 , 240};
    Style GitStaged     = { 15  , 22};
    Style GitNotStaged  = { 15  , 130};
    Style GitUntracked  = { 15  , 52};
    Style GitConflicted = { 15  , 9};
    Style GitStashed    = { 15  , 20};
    Style VirtualEnv    = { 0   , 35};
    Style VirtualGo     = { 0   , 35};
    Style Perlbrew      = { 0   , 20};
    Style TFWs          = { 15  , 26};
    Style Time          = { 15  , 236};
    Style ShellVar      = { 52  , 11};
    Style Node          = { 15  , 40};
    Style Load          = { 15  , 22};
    Style NixShell      = { 0   , 69};
    Style Duration      = { 250 , 237};
};

#endif
