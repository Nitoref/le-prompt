#ifndef THEME_H
#define THEME_H

// #include "include/json.hpp"
// using nlohmann::json;


struct ShellInfo;
struct Symbols;
struct Style;
struct Theme;

const extern ShellInfo Bash;
const extern ShellInfo Zsh;
const extern ShellInfo Bare;

const extern Symbols AnglySymbols;
const extern Symbols CurvySymbols;
const extern Symbols FlatSymbols;

const extern Theme   Default;
const extern Theme   SolarizedDark16;
const extern Theme   SolarizedLight16;
const extern Theme   LowContrast;



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
    const char* Lock;
    const char* Network;
    const char* Separator;
    const char* SeparatorThin;
    const char* GitBranch;
    const char* GitDetached;
    const char* GitAhead;
    const char* GitBehind;
    const char* GitStaged;
    const char* GitNotStaged;
    const char* GitConflicted;
    const char* GitUntracked;
};

typedef enum {
    TEXT_BOLD        = (1u << 0),
    TEXT_FAINT       = (1u << 1),
    TEXT_ITALIC      = (1u << 2),
    TEXT_UNDERLINE   = (1u << 3),
    TEXT_BLINK_1     = (1u << 4),
    TEXT_BLINK_2     = (1u << 5),
    TEXT_CROSSED_OUT = (1u << 6),
    TEXT_FRAMED      = (1u << 7),
    TEXT_ENCIRCLED   = (1u << 8),
    TEXT_OVERLINED   = (1u << 9)
} text_style;

struct Style
{
    Style() = default;
    int   fg;
    int   bg;
    // text_style opt;
};


struct Theme
{
    Style Separator;
    Style Username;
    Style UsernameRoot;
    Style Hostname;
    Style Home;
    Style Path;
    Style Cwd;
    Style Readonly;
    Style Ssh;
    Style DockerMachine;
    Style KubeCluster;
    Style KubeNamespace;
    Style DotEnv;
    Style Aws;
    Style RepoClean;
    Style RepoDirty;
    Style Jobs;
    Style CmdPassed;
    Style CmdFailed;
    Style SvnChanges;
    Style GitAhead;
    Style GitBehind;
    Style GitStaged;
    Style GitNotStaged;
    Style GitUntracked;
    Style GitConflicted;
    Style GitStashed;
    Style VirtualEnv;
    Style VirtualGo;
    Style Perlbrew;
    Style TFWs;
    Style Time;
    Style ShellVar;
    Style Node;
    Style Load;
    Style NixShell;
    Style Duration;
};


// void to_json(json& j, const Style& s);
// void from_json(const json& j, Style& s);

// void to_json(json& j, const Style& s);
// void from_json(const json& j, Style& s);


#endif
