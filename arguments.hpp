#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <string>
#include <vector>
#include "cpptoml.hpp"

struct Arguments
{
    Arguments() = default;
    Arguments(std::shared_ptr<cpptoml::table> args);

     int term_width        = 0;
     int prev_error        = 0;
     int cwd_max_depth      = 0;
     int cwd_max_dir_size    = 0;
     int max_width_ratio    = 0;
     int max_segment_width  = 0;
    bool colorize_hostname = false;
    bool numeric_exit_codes = false;
    bool shorten_gke_names  = false;
    const char* git_mode   = "simple";
    const char* cwd_mode   = "simple";
    const char* shell     = NULL;
    const char* ignore_repos = NULL;
    const char* duration = NULL;
    std::vector<std::string> left_segments = {"user","host","pwd","root","exit"};
    std::vector<std::string> right_segments = {"git"};
    std::vector<std::pair<std::string, std::string>> path_aliases;
};

extern Arguments DefaultArgs;

#endif
