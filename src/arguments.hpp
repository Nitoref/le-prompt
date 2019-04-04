#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <map>
#include <vector>
#include "string.hpp"

struct Arguments
{
    Arguments() = default;
    int    term_width         = 0;
    int    prev_error         = 0;
    int    cwd_max_depth      = 0;
    int    cwd_max_dir_size   = 0;
    int    max_width_ratio    = 0;
    int    max_segment_width  = 0;
    bool   colorize_hostname  = false;
    bool   numeric_exit_codes = false;
    bool   shorten_gke_names  = false;
    string git_mode           = "simple";
    string cwd_mode           = "simple";
    string ignore_repos       = "";
    string shell              = "";
    string duration           = "";
    std::vector<std::string> left_segments  = {"user","host","root"};
    std::vector<std::string> right_segments;
    std::map<std::string, std::string> path_aliases;
};


#endif
