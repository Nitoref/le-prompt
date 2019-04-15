#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <map>
#include <vector>
#include <string>


struct Arguments
{
    using str    = std::string;
    using strvec = std::vector<str>;
    using strmap = std::map<str, str>;

    Arguments() = default;

    int  timeout = 1000;
    
    int  width_limit    = 0;
    int  padding_left   = 1;
    int  padding_right  = 1;
    int  padding_end    = 1;

    bool force_newline  = false;
    bool native_rprompt = false;
     
    bool numeric_exit  = false;
    bool jobs_count    = true;

    str default_user = "";
    str default_host = "";
    str time_format  = "%T";

    bool cwd_fancy   = false;
    int  cwd_depth   = 0;
    int  cwd_dir_limit = 0;

    str    git_format  = "@.><+!?x";
    bool   git_compact = false;
    bool   git_count   = true;
    strvec git_ignore  = {};

    strmap path_aliases     = {};
    strvec left_segments    = {"user","host","pwd","shell"};
    strvec right_segments   = {"time", "git"};
    strvec newline_segments = {};
};


#endif
