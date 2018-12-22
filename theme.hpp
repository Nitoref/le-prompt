#ifndef THEME_H
#define THEME_H


struct ShellInfo
{
    std::string colorTemplate;
    std::string rootIndicator;
    std::string escapedBackslash;
    std::string escapedBacktick;
    std::string escapedDollar;
};


struct Symbols
{
    std::string Lock;
    std::string Network;
    std::string Separator;
    std::string SeparatorThin;
    std::string GitBranch;
    std::string GitDetached;
    std::string GitAhead;
    std::string GitBehind;
    std::string GitStaged;
    std::string GitNotStaged;
    std::string GitConflicted;
    std::string GitUntracked;
};


struct Style
{
    int          fg;
    int          bg;
    std::string opt;
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
