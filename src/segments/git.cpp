#include "modules.hpp"
#include "utils.hpp"
#include <string>
#include <tuple>
#include <git2.h>
#include <string.h>
#ifdef _WIN32
# include <Windows.h>
#else
# include <unistd.h>
#endif


struct GitStatus
{
    std::string name;
    std::string tag;
    std::string hash;
    size_t stash  = 0;
    size_t ahead  = 0;
    size_t behind = 0;
    size_t staged = 0;
    size_t notstaged = 0;
    size_t untracked  = 0;
    size_t conflicted = 0;
    bool tagged   = false;
    bool empty    = false;
    bool detached = false;
    bool ignored  = false;
};


int status_callback(const char* path, unsigned int status_flags, void* status);
int get_git_status(GitStatus& status, std::vector<std::string> ignored_repositories);
int get_ahead_behind(GitStatus& status, git_repository *repo, git_reference *head);
int get_stats(GitStatus& status, git_status_list *status_list);
int get_stash(size_t index, const char *message, const git_oid *stash_id, void *status);
int get_name(GitStatus& status, git_repository *repo);


Module
SegmentGit(const config& c)
{
    GitStatus status;
 

    if (get_git_status(status, c.git.ignore))
    {
        return Module {};
    };


    bool dirty = status.ahead     || status.behind
              || status.staged    || status.notstaged
              || status.untracked || status.conflicted;


    std::string branch_symbol;
    if (status.detached && c.git.hash_fallback){
        status.name   = status.hash;
        branch_symbol = c.git.symbol_hash;
    }
    else{
        branch_symbol = c.git.symbol_branch;
    }


    if (!c.git.fancy)
    {
        std::string content;
        for (char ch: c.git.format)
        {
            switch (ch) {
                case '@': if (!status.name.empty()) content += branch_symbol + status.name; break;
                case '%': if (!status.tag.empty())  content += c.git.symbol_tag + status.tag; break;
                case '.': if (status.stash      ) content += c.git.symbol_stash; break;
                case '>': if (status.ahead      ) content += c.git.symbol_ahead; break;
                case '<': if (status.behind     ) content += c.git.symbol_behind; break;
                case '+': if (status.staged     ) content += c.git.symbol_staged; break;
                case '!': if (status.notstaged  ) content += c.git.symbol_notstaged; break;
                case '?': if (status.untracked  ) content += c.git.symbol_untracked; break;
                case 'x': if (status.conflicted ) content += c.git.symbol_conflicted; break;
                case 'd': content += dirty ? c.git.symbol_dirty : ""; break;
                default: break;
            }
        }
        return Module { {
            module::id::git_branch, content,
            !status.ignored ? (dirty ? c.git.theme_dirty
                                     : c.git.theme_clean)
                            : c.git.theme_ignored
        } };
    }

    
    Module    module;
    
    for (char ch: c.git.format)
    {
        switch (ch)
        {
        case '@':
            module.emplace_back(
                module::id::git_branch,
                branch_symbol + status.name,
                !status.ignored ? (dirty ? c.git.theme_dirty
                                         : c.git.theme_clean)
                                : c.git.theme_ignored
            );
        break;
        case '%':
            if (status.tagged) {
                module.emplace_back(
                    module::id::git_tag,
                    c.git.symbol_tag + status.tag,
                    c.git.theme_tag
                );
            }
        break;
        case '.':
            if (status.stash) {
                std::string count = c.git.count ? std::to_string(status.stash) : "";
                module.emplace_back(
                    module::id::git_stash,
                    count + c.git.symbol_stash,
                    c.git.theme_stash
                );
            }
        break;
        case '>':
            if (status.ahead) {
                std::string count = c.git.count ? std::to_string(status.ahead) : "";
                module.emplace_back(
                    module::id::git_ahead,
                    count + c.git.symbol_ahead,
                    c.git.theme_ahead
                );
            }
        break;
        case '<':
            if (status.behind) {
                std::string count = c.git.count ? std::to_string(status.behind) : "";
                module.emplace_back(
                    module::id::git_behind,
                    count + c.git.symbol_behind,
                    c.git.theme_behind
                );
            }
        break;
        case '+':
            if (status.staged) {
                std::string count = c.git.count ? std::to_string(status.staged) : "";
                module.emplace_back(
                    module::id::git_staged,
                    count + c.git.symbol_staged,
                    c.git.theme_staged
                );
            }
        break;
        case '!':
            if (status.notstaged) {
                std::string count = c.git.count ? std::to_string(status.notstaged) : "";
                module.emplace_back(
                    module::id::git_notstaged,
                    count + c.git.symbol_notstaged,
                    c.git.theme_notstaged
                );
            }
        break;
        case '?':
            if (status.untracked) {
                std::string count = c.git.count ? std::to_string(status.untracked) : "";
                module.emplace_back(
                    module::id::git_untracked,
                    count + c.git.symbol_untracked,
                    c.git.theme_untracked
                );
            }
        break;
        case 'x':
            if (status.conflicted) {
                std::string count = c.git.count ? std::to_string(status.conflicted) : "";
                module.emplace_back(
                    module::id::git_conflicted,
                    count + c.git.symbol_conflicted,
                    c.git.theme_conflicted
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
get_git_status(GitStatus& status, std::vector<std::string> ignored_repositories)
{
    git_repository     *repository = NULL;
    git_status_options status_opt  = GIT_STATUS_OPTIONS_INIT;
    git_status_list    *status_list;
 
    git_libgit2_opts(GIT_OPT_ENABLE_STRICT_HASH_VERIFICATION, 0);
    git_libgit2_opts(GIT_OPT_DISABLE_INDEX_CHECKSUM_VERIFICATION, 1);
    git_libgit2_opts(GIT_OPT_DISABLE_INDEX_FILEPATH_VALIDATION, 1);
    git_libgit2_init();

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


    if (git_repository_is_empty(repository))
    {
        status.empty = true;
        return 0;
    }


    if (get_name(status, repository))
    {
        return 1; 
    }

    if (git_repository_is_bare(repository))
    {
        return 0;
    }

    std::string workdir = utils::string(
        git_repository_workdir(repository)
    );
    for (auto path: ignored_repositories)
    {
        if (workdir == path) {
            status.ignored = true;
            return 0;
        }
    }

    // if (git_status_list_new(&status_list, repository, &status_opt))
    // {
    //     return 1;
    // }

    git_status_foreach_ext(
        repository, &status_opt, status_callback, (void*)&status
    );

    // if (get_stats(status, status_list))
    // {
    //     return 1;
    // }
    git_stash_foreach(repository, &get_stash, (void*)&status);

    git_status_list_free(status_list);
    git_repository_free(repository);
    git_libgit2_shutdown();
    return 0;
}


int
get_stash(size_t index, const char *message, const git_oid *stash_id, void *status)
{
    ((GitStatus*)status)->stash ++;
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

    // std::cout << git_reference_name(upstream) << "\n";

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
        if (error == GIT_ENOTFOUND || error == GIT_EUNBORNBRANCH)
        {
            status.name  = "HEAD (no branch)";
        }
        else
        {
            return 1;
        }
    }
    else
    {
        status.name = git_reference_shorthand(head);
    }

    char *oid_str = (char*)malloc(8*sizeof(char));
    git_oid_tostr(
        oid_str, sizeof(oid_str), git_reference_target(head)
    );
    status.hash = utils::string(oid_str);

    if (git_reference_is_tag(head))
    {
        git_tag *tag;
        git_tag_lookup(&tag, repo, git_reference_target(head));
        status.tag = utils::string(git_tag_name(tag));
    }

    if (git_repository_head_detached(repo))
    {
        status.detached = true;
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
               status.notstaged++;
           }
        }
    }
    return 0;
}



int
status_callback(const char* path, unsigned int status_flags, void* status)
{

    if (status_flags == GIT_STATUS_CURRENT 
    ||  status_flags & GIT_STATUS_IGNORED)
    {
        return 0;
    }

    if (status_flags & GIT_STATUS_CONFLICTED)
    {
        ((GitStatus*)status)->conflicted ++;
    }
    else
    if (status_flags & ( GIT_STATUS_WT_RENAMED
                    | GIT_STATUS_WT_NEW))
    {
        ((GitStatus*)status)->untracked++;
    }
    else {
       if (status_flags & ( GIT_STATUS_INDEX_NEW
                       | GIT_STATUS_INDEX_DELETED
                       | GIT_STATUS_INDEX_RENAMED
                       | GIT_STATUS_INDEX_MODIFIED
                       | GIT_STATUS_INDEX_TYPECHANGE))
       {
           ((GitStatus*)status)->staged++;
       }
       if (status_flags & ( GIT_STATUS_WT_DELETED
                       | GIT_STATUS_WT_RENAMED
                       | GIT_STATUS_WT_MODIFIED
                       | GIT_STATUS_WT_TYPECHANGE))
       {
           ((GitStatus*)status)->notstaged++;
       }
    }
    return 1;
}
