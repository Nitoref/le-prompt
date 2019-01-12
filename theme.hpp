#ifndef THEME_H
#define THEME_H

#include "cpptoml.hpp"


struct Shell
{
    Shell() = default;
    Shell(const char *sh);
    const char* escape_    ;//= "\\[\\e[";
    const char* epacse_    ;//= "m\\]";
    const char* indicator_ ;//= "\\$";
    const char* backslash_ ;//= "\\\\";
    const char* backtick_  ;//= "\\`";
    const char* dollar_    ;//= "\\$";
};

struct Symbols
{
    Symbols() = default;
    Symbols(std::shared_ptr<cpptoml::table> syms);
    const char* lock           = "\uE0A2"; // ""
    const char* network        = "\uE0A2"; // ""
    const char* separator      = "\uE0B4"; // ""
    const char* r_separator     = "\uE0B4"; // ""
    const char* separator_thin  = "\uE0B5"; // ""
    const char* r_separator_thin = "\uE0B5"; // ""
    const char* git_branch      = "\uE0A0"; // ""
    const char* git_detached    = "\u27A6"; // "➦"
    const char* git_ahead       = "\u2B06"; // "⬆"
    const char* git_behind      = "\u2B07"; // "⬇"
    const char* git_staged      = "\u2714"; // "✔"
    const char* git_not_staged   = "\u270E"; // "✎"
    const char* git_conflicted  = "\u273C"; // "✼"
    const char* git_untracked   = "\u2026"; // "…"
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
    Style separator     = { 15  , 0 } ;
    Style username      = { 250 , 240};
    Style username_root  = { 250 , 124};
    Style hostname      = { 250 , 238};
    Style home          = { 15  , 31};
    Style path          = { 250 , 237};
    Style cwd           = { 254 , 237};
    Style readonly      = { 254 , 124};
    Style ssh           = { 254 , 166};
    Style docker_machine = { 177 , 55};
    Style kubeCluster   = { 117 , 26};
    Style kube_namespace = { 170 , 17};
    Style do_tEnv        = { 15  , 55};
    Style aws           = { 15  , 22};
    Style repo_clean     = { 0   , 148};
    Style repo_dirty     = { 15  , 161};
    Style jobs          = { 39  , 238};
    Style cmd_passed     = { 15  , 236};
    Style cmd_failed     = { 15  , 161};
    Style svn_changes    = { 22  , 148};
    Style git_ahead      = { 250 , 240};
    Style git_behind     = { 250 , 240};
    Style git_staged     = { 15  , 22};
    Style git_not_staged  = { 15  , 130};
    Style git_untracked  = { 15  , 52};
    Style git_conflicted = { 15  , 9};
    Style git_stashed    = { 15  , 20};
    Style virtual_env    = { 0   , 35};
    Style virtual_go     = { 0   , 35};
    Style perlbrew      = { 0   , 20};
    Style TFWs          = { 15  , 26};
    Style time          = { 15  , 236};
    Style shell_var      = { 52  , 11};
    Style node          = { 15  , 40};
    Style load          = { 15  , 22};
    Style nix_shell      = { 0   , 69};
    Style duration      = { 250 , 237};
};

#endif
