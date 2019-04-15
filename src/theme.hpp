#ifndef THEME_H
#define THEME_H

struct Style
{
    int   fg = -1;
    int   bg = -1;
};

struct Theme
{
    Theme() = default;
    
    Style separator;
    Style exit_success;
    Style exit_failure;
    
    Style username;
    Style root;
    Style hostname;
    Style home;
    Style path;
    Style cwd;
    Style readonly;
    
    Style ssh;
    Style docker;
    Style dot_env;
    Style aws;
    Style jobs;
    Style virtual_env;
    Style time;
    Style duration;

    Style git_clean;
    Style git_dirty;
    Style git_stash;
    Style git_ahead;
    Style git_behind;
    Style git_staged;
    Style git_nstaged;
    Style git_untracked;
    Style git_conflicted;
    
};


#endif
