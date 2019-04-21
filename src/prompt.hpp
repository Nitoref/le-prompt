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
    std::unordered_set<module::id> ignored_segments;

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

    std::vector<module::id> priority_list
    {
        module::id::extension,
        module::id::shell,
        module::id::status,
        module::id::jobs,
        module::id::time,
        module::id::perms,
        module::id::git_branch,
        module::id::dir,
        module::id::path,
        module::id::home,
        module::id::load,
        module::id::docker,
        module::id::git_tag,
        module::id::git_ahead,
        module::id::git_behind,
        module::id::git_staged,
        module::id::git_notstaged,
        module::id::git_untracked,
        module::id::git_conflicted,
        module::id::git_stash,
        module::id::host,
        module::id::user,
        module::id::context,
        module::id::ssh,
        module::id::aws,
        module::id::venv,
    };
};
#endif
