#ifndef PROMPT_H
#define PROMPT_H

#include <unordered_set> 
#include <unordered_map> 
#include <functional>
#include <future>
#include <vector>
#include <string>

#include "subprompt.hpp"
#include "printer.hpp"
#include "modules.hpp"
#include "utils.hpp"


class Prompt
{
public:

    // Constructor
    Prompt(config& config);

    // configuration
    config  conf;
    
    // Subprompts
    SubPrompt left;
    SubPrompt right;
    SubPrompt down;
    
    // Ignored segments
    std::unordered_set<segment::id> ignored_segments;

    // 
    std::string
    make();

    // 
    void
    shrink();

    //
    std::string
    print_native();
    
    //
    std::string
    print_emulated();


    int prev_color_  = -2;

    std::vector<segment::id> priority_list
    {
        segment::id::extension,
        segment::id::shell,
        segment::id::status,
        segment::id::jobs,
        segment::id::time,
        segment::id::perms,
        segment::id::git_branch,
        segment::id::hg,
        segment::id::dir_cwd,
        segment::id::dir_path,
        segment::id::dir_home,
        segment::id::load,
        segment::id::docker,
        segment::id::git_tag,
        segment::id::git_ahead,
        segment::id::git_behind,
        segment::id::git_staged,
        segment::id::git_notstaged,
        segment::id::git_untracked,
        segment::id::git_conflicted,
        segment::id::git_stash,
        segment::id::host,
        segment::id::user,
        segment::id::context,
        segment::id::ssh,
        segment::id::aws,
        segment::id::venv,
    };
};
#endif
