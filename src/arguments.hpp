#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <map>
#include <vector>
#include <string>
#include <chrono>

using duration = std::chrono::milliseconds;

struct Arguments
{
    Arguments() = default;
            int cwd_max_depth      = 0;
            int cwd_max_dir_size   = 0;
            int max_width_ratio    = 0;
            int max_segment_width  = 0;
            int padding            = 1;
           bool colorize_hostname  = false;
           bool numeric_exit_codes = false;
           bool shorten_gke_names  = false;
       duration request_timeout    = duration(1000);
    std::string default_user       = "";
    std::string default_host       = "";
    std::string time_format        = "%T";
    std::string git_format         = "@><+-?!%";
    std::string cwd_mode           = "fancy";
    std::vector<std::string> git_ignore     = {};
    std::vector<std::string> left_segments  = {"user","host","pwd","root"};
    std::vector<std::string> right_segments = {"time", "git"};
    std::map<std::string, std::string> path_aliases;
};


#endif
