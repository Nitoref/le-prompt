#include <git2.h>
#include <string.h>
#include <stdio.h>
#ifdef _WIN32
# include <Windows.h>
#else
# include <unistd.h>
#endif
#include "modules.hpp"
#include "utils.hpp"
#include <string>
#include <tuple>


struct GitStatus
{
    std::string name;
    size_t stash  = 0;
    size_t ahead  = 0;
    size_t behind = 0;
    size_t staged = 0;
    size_t nstaged = 0;
    size_t untracked  = 0;
    size_t conflicted = 0;
    bool detached = false;
    bool good = true;
    bool empty = false;
};


int get_git_status(GitStatus& status, std::vector<std::string> ignored_repositories);
int get_ahead_behind(GitStatus& status, git_repository *repo, git_reference *head);
int get_stats(GitStatus& status, git_status_list *status_list);
int get_name(GitStatus& status, git_repository *repo);


Module
SegmentGit(const Config& c)
{
    GitStatus status;
 

    if (get_git_status(status, c.args.git_ignore))
    {
        return Module {};
    };


    if (status.name.empty())
    {
        return Module {};
    }

    bool dirty = status.ahead     || status.behind
              || status.staged    || status.nstaged
              || status.untracked || status.conflicted;


    std::string branch_symbol;
    if (status.detached)
        branch_symbol = c.symbols.git_hash;
    else
        branch_symbol = c.symbols.git_branch;


    if (c.args.git_compact)
    {
        std::string content;
        for (char ch: c.args.git_format)
        {
            switch (ch) {
                case '@': content += branch_symbol + status.name; break;
                case 'd': content += dirty ? c.symbols.git_dirty : ""; break;
                case '.': content += status.stash ? c.symbols.git_stash : ""; break;
                case '>': content += status.ahead ? c.symbols.git_ahead : ""; break;
                case '<': content += status.behind ? c.symbols.git_behind : ""; break;
                case '+': content += status.staged ? c.symbols.git_staged : ""; break;
                case '!': content += status.nstaged ? c.symbols.git_nstaged : ""; break;
                case '?': content += status.untracked ? c.symbols.git_untracked : ""; break;
                case 'x': content += status.conflicted ? c.symbols.git_conflicted : ""; break;
                default: break;
            }
        }
        return Module { {
            module::id::git_branch, content,
            dirty ? c.theme.git_dirty : c.theme.git_clean
        } };
    }

    
    Module    module;
    // Segment  segment;
    
    for (char ch: c.args.git_format)
    {
        switch (ch)
        {
        case '@':
            module.emplace_back(
                module::id::git_branch,
                branch_symbol + status.name,
                dirty ? c.theme.git_dirty : c.theme.git_clean
            );
        break;
        case '.':
            if (status.stash) {
                std::string count = c.args.git_count ? std::to_string(status.stash) : "";
                module.emplace_back(
                    module::id::git_stash,
                    count + c.symbols.git_stash,
                    c.theme.git_stash
                );
            }
        break;
        case '>':
            if (status.ahead) {
                std::string count = c.args.git_count ? std::to_string(status.ahead) : "";
                module.emplace_back(
                    module::id::git_ahead,
                    count + c.symbols.git_ahead,
                    c.theme.git_ahead
                );
            }
        break;
        case '<':
            if (status.behind) {
                std::string count = c.args.git_count ? std::to_string(status.behind) : "";
                module.emplace_back(
                    module::id::git_behind,
                    count + c.symbols.git_behind,
                    c.theme.git_behind
                );
            }
        break;
        case '+':
            if (status.staged) {
                std::string count = c.args.git_count ? std::to_string(status.staged) : "";
                module.emplace_back(
                    module::id::git_staged,
                    count + c.symbols.git_staged,
                    c.theme.git_staged
                );
            }
        break;
        case '!':
            if (status.nstaged) {
                std::string count = c.args.git_count ? std::to_string(status.nstaged) : "";
                module.emplace_back(
                    module::id::git_nstaged,
                    count + c.symbols.git_nstaged,
                    c.theme.git_nstaged
                );
            }
        break;
        case '?':
            if (status.untracked) {
                std::string count = c.args.git_count ? std::to_string(status.untracked) : "";
                module.emplace_back(
                    module::id::git_untracked,
                    count + c.symbols.git_untracked,
                    c.theme.git_untracked
                );
            }
        break;
        case 'x':
            if (status.conflicted) {
                std::string count = c.args.git_count ? std::to_string(status.conflicted) : "";
                module.emplace_back(
                    module::id::git_conflicted,
                    count + c.symbols.git_conflicted,
                    c.theme.git_conflicted
                );
            }
        break;
        default:
            break;
        }
    }
    return module;
}



int
get_stashed(size_t index, const char *message, const git_oid *stash_id, void *status)
{
    ((GitStatus*)status)->stash ++;
    return 0;
}


int
get_git_status(GitStatus& status, std::vector<std::string> ignored_repositories)
{
    git_repository     *repository = NULL;
    git_status_options status_opt  = GIT_STATUS_OPTIONS_INIT;
    git_status_list    *status_list;
 
    git_libgit2_init();
    git_libgit2_opts(GIT_OPT_ENABLE_STRICT_HASH_VERIFICATION, 0);

    status_opt.show  = GIT_STATUS_SHOW_INDEX_AND_WORKDIR;

    status_opt.flags = GIT_STATUS_OPT_INCLUDE_UNTRACKED 
                    | GIT_STATUS_OPT_RENAMES_INDEX_TO_WORKDIR
                    | GIT_STATUS_OPT_EXCLUDE_SUBMODULES
                    | GIT_STATUS_OPT_NO_REFRESH
                    | GIT_STATUS_OPT_SORT_CASE_SENSITIVELY;

    if (git_repository_open_ext(&repository, ".", 0, NULL))
    {
        return 1;
    }

    std::string workdir = utils::string::safe(
        git_repository_workdir(repository)
    );
    for (auto path: ignored_repositories)
    {
        if (workdir == path) return 1;
    }

    if (get_name(status, repository))
    {
        return 1; 
    }

    if (git_repository_is_bare(repository))
    {
        return 0;
    }

    if (git_status_list_new(&status_list, repository, &status_opt))
    {
        return 1;
    }

    if (get_stats(status, status_list))
    {
        return 1;
    }
    git_stash_foreach(repository, &get_stashed, (void*)&status);

    git_status_list_free(status_list);
    git_repository_free(repository);
    git_libgit2_shutdown();
    return 0;
}


int
get_ahead_behind(GitStatus& status, git_repository *repo, git_reference *head)
{
    int    error;
    git_reference *upstream = NULL;

    error = git_branch_upstream(&upstream, head);
    if (error)
    {
        return error;
    }

    git_graph_ahead_behind(
        &status.ahead, &status.behind,
        repo,
        git_reference_target(head),
        git_reference_target(upstream)
    );
    return 0;
}


int
get_name(GitStatus& status, git_repository *repo)
{
    git_reference *head     = NULL;

    int error = git_repository_head(&head, repo);
    if (error)
    {
        if (error == GIT_ENOTFOUND)
        {
            status.name = "HEAD (no branch)";
        }
        else 
        if (error == GIT_EUNBORNBRANCH)
        {
            status.name  = "HEAD (no commit)";
            status.empty = true;
            return 1;
        }
        else
        {
            return 1;
        }
    }

    if (git_repository_head_detached(repo))
    {
        char *branch_cstr = (char*)malloc(8*sizeof(char));
        git_oid_tostr(
            branch_cstr, sizeof(branch_cstr), git_reference_target(head)
        );
        status.name = branch_cstr;
        status.detached = true;
    }
    else
    {
        status.name = git_reference_shorthand(head);
    }

    get_ahead_behind(status, repo, head);
    git_reference_free(head);
    return 0;
}


int
get_stats(GitStatus& status, git_status_list *status_list)
{
    size_t entrycount = git_status_list_entrycount(status_list);

    const git_status_entry *s;
    for (size_t i = 0; i < entrycount; ++i)
    {
        s = git_status_byindex(status_list, i);

        if (s->status == GIT_STATUS_CURRENT 
        ||  s->status & GIT_STATUS_IGNORED)
        {
            continue;
        }

        if (s->status & GIT_STATUS_CONFLICTED)
        {
            status.conflicted ++;
        }
        else
        if (s->status & ( GIT_STATUS_WT_RENAMED
                        | GIT_STATUS_WT_NEW))
        {
            status.untracked++;
        }
        else {
           if (s->status & ( GIT_STATUS_INDEX_NEW
                           | GIT_STATUS_INDEX_DELETED
                           | GIT_STATUS_INDEX_RENAMED
                           | GIT_STATUS_INDEX_MODIFIED
                           | GIT_STATUS_INDEX_TYPECHANGE))
           {
               status.staged++;
           }
           if (s->status & ( GIT_STATUS_WT_DELETED
                           | GIT_STATUS_WT_RENAMED
                           | GIT_STATUS_WT_MODIFIED
                           | GIT_STATUS_WT_TYPECHANGE))
           {
               status.nstaged++;
           }
        }
    }
    return 0;
}
