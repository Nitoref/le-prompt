#ifndef THEME_H
#define THEME_H


struct ShellInfo;
extern ShellInfo Bash;
extern ShellInfo Zsh;
extern ShellInfo Bare;

struct Symbols;
extern Symbols AnglySymbols;
extern Symbols CurvySymbols;
extern Symbols FlatSymbols;

struct Theme;
extern Theme   Default;
extern Theme   SolarizedDark16;
extern Theme   SolarizedLight16;
extern Theme   LowContrast;


struct ShellInfo
{
    const char* colorTemplate;
    const char* rootIndicator;
    const char* escapedBackslash;
    const char* escapedBacktick;
    const char* escapedDollar;
};

struct Symbols
{
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


struct Style
{
    int   fg;
    int   bg;
    char* opt;
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

#endif