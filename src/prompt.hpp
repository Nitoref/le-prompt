#ifndef PROMPT_H
#define PROMPT_H

#include <unordered_set> 
#include <unordered_map> 
#include <functional>
#include <future>
#include <vector>
#include <string>

#include "printer.hpp"
#include "modules.hpp"
#include "utils.hpp"


class SubPrompt
{
public:
    
    // Constructor
    template<typename F>
    SubPrompt (std::string a, std::string b, int c, int d, F f):
    separator(a),
    separator2(b),
    separator_length(utils::strlen(a)),
    separator2_length(utils::strlen(b)),
    padding_left(c),
    padding_right(d),
    append(f)
    {}

    // Content
    std::vector<Segment> segments;

    // Symbols
    std::string separator;
    std::string separator2;
    int separator_length;
    int separator2_length;
    int padding_left;
    int padding_right;

    // Information
    size_t length = 0;
    size_t actual_length = 0;

    std::vector<std::vector<int>> id_lookup;

    // Output status
    int prev_color  = -2;

    // Output function
    std::function<
        void(std::string&, std::string)
    >append;

    void
    preformat();
    
    std::string
    format_without(std::unordered_set<module::id>& ignored);

    inline std::string
    format_segment(Segment s);
    
    inline std::string
    make_separator(Segment s);
    
    inline std::string
    final_separator();
};


class Prompt
{
public:

    // Constructor
    Prompt(config& config);

    // configuration
    config  options;
    
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
        module::id::git_ahead,
        module::id::git_behind,
        module::id::git_staged,
        module::id::git_nstaged,
        module::id::git_untracked,
        module::id::git_conflicted,
        module::id::git_stash,
        module::id::user,
        module::id::context,
        module::id::ssh,
        module::id::aws,
        module::id::virtual_env,
    };
};
#endif
