#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <map>
#include <vector>
#include <string>


struct Arguments
{
    using string = std::string;
    using strvec = std::vector<string>;
    using strmap = std::map<string, string>;

    Arguments() = default;
    
    strvec left_segments    = {"user","host","pwd","shell"};
    strvec right_segments   = {"time", "git", "exit", "root"};
    strvec down_segments = {};

    int  timeout = 1000;
    
    int  width_limit    = 0;
    int  padding_left   = 1;
    int  padding_right  = 1;
    int  padding_end    = 1;

    bool force_newline  = false;
    bool native_rprompt = false;
    
    bool numeric_status  = false;
    bool jobs_count    = true;

    string default_user = "";
    string default_host = "";
    string time_format  = "%T";

    bool dir_fancy   = false;
    int  dir_depth   = 0;
    int  dir_length = 0;

    string git_format  = "@.><+!?x";
    bool   git_fancy   = true;
    bool   git_count   = true;
    strvec git_ignore  = {};

    strmap path_aliases = {};
};


#endif
