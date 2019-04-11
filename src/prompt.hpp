#ifndef PROMPT_H
#define PROMPT_H

#include <unordered_set> 
#include <unordered_map> 
#include <future>
#include <vector>
#include <string>

#include "printer.hpp"
#include "modules.hpp"


class Prompt
{
public:
    Prompt(Config config);
    
    void
    shrink();

    std::string
    print();

    std::string
    format_left_segments();
    
    std::string
    format_right_segments();

    Config  options;
    Printer printer;
    int prev_color_  = -1;

    std::vector<module::id> priority_list_
    {
        module::id::user,
        module::id::shell,
        module::id::host,
        module::id::exit,
        module::id::jobs,
        module::id::time,
        module::id::perms,
        module::id::cwd,
        module::id::path,
        module::id::home,
        module::id::git_branch,
        module::id::git_ahead,
        module::id::git_behind,
        module::id::git_staged,
        module::id::git_not_staged,
        module::id::git_untracked,
        module::id::git_conflicted,
        module::id::git_stash,
        module::id::ssh,
        module::id::aws,
        module::id::virtual_env,
    };

    std::vector<Segment> left_segments;
    std::vector<Segment> right_segments;

private:

    size_t left_length_;
    size_t right_length_;
    std::unordered_set<module::id> ignored_segments_;

    size_t 
    length(std::vector<Segment> segments);

    std::string
    format_segment(Segment s);
    
    std::string
    make_separator(Segment s, std::string regular, std::string thin);
    
    std::string
    end_separator(std::string separator);
    
    std::string
    format_left_segment(Segment s);
    
    std::string 
    format_right_segment(Segment s);
    std::string 
    format_segments(std::vector<Segment> segments, bool policy);

};
#endif
