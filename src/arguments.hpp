#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <map>
#include <vector>
#include <string>

struct Arguments
{
    Arguments() = default;
            int cwd_max_depth      = 0;
            int cwd_max_dir_size   = 0;
            int max_width_ratio    = 0;
            int max_segment_width  = 0;
           bool colorize_hostname  = false;
           bool numeric_exit_codes = false;
           bool shorten_gke_names  = false;
    std::string default_user       = "";
    std::string default_host       = "";
    std::string time_format        = "%T";
    std::string git_mode           = "simple";
    std::string cwd_mode           = "simple";
    std::string shell              = "";
    std::string duration           = "";
    std::vector<std::string> ignore_repos   = {};
    std::vector<std::string> left_segments  = {"user","host","root"};
    std::vector<std::string> right_segments = {};
    std::map<std::string, std::string> path_aliases;
};


#endif
