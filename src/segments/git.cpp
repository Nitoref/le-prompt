#include <git2.h>
#include <string.h>
#include <stdio.h>
#ifdef _WIN32
# include <Windows.h>
#else
# include <unistd.h>
#endif
#include "../modules.hpp"
#include <mutex>


struct GitStatus
{
    std::string name;
    size_t ahead  = 0;
    size_t behind = 0;
    size_t staged = 0;
    size_t not_staged  = 0;
    size_t untracked  = 0;
    size_t conflicted = 0;
};

int get_git_status(GitStatus& status);
int get_stats(GitStatus& status, git_status_list *status_list);
int get_ahead_behind(GitStatus& status, git_repository *repo, git_reference *head);
int get_name(GitStatus& status, git_repository *repo);


// void SegmentGitName::make()
// {
//     GitStatus& status = git_status__;
//     get_git_status_threadsafe(status);
//     if (status.name.empty())
//         return;

//     segment.content = opt.symbols.git_branch;
//     segment.content += ' ';
//     segment.content += status.name;
//     if (  status.ahead     || status.behind
//        || status.staged    || status.not_staged
//        || status.untracked || status.conflicted
//     )
//         segment.style = opt.theme.repo_dirty;
//     else
//         segment.style = opt.theme.repo_clean;
// };

// void
// SegmentGitAhead::make()
// {
//     GitStatus& status = git_status__;
//     if (status.ahead)
//     {
//         segment.style   =  opt.theme.git_ahead;
//         segment.content =  std::to_string(status.ahead);
//         segment.content += opt.symbols.git_ahead;
//     }
// };
// void
// SegmentGitBehind::make()
// {
//     GitStatus& status = git_status__;
//     if (status.behind)
//     {
//         segment.style   =  opt.theme.git_behind;
//         segment.content =  std::to_string(status.behind);
//         segment.content += opt.symbols.git_behind;
//     }
// };
// void
// SegmentGitStaged::make()
// {
//     GitStatus& status = git_status__;
//     if (status.staged)
//     {
//         segment.style   =  opt.theme.git_staged;
//         segment.content =  std::to_string(status.staged);
//         segment.content += opt.symbols.git_staged;
//     }
// };
// void
// SegmentGitNotStaged::make()
// {
//     GitStatus& status = git_status__;
//     if (status.not_staged)
//     {
//         segment.style   =  opt.theme.git_not_staged;
//         segment.content =  std::to_string(status.not_staged);
//         segment.content += opt.symbols.git_not_staged;
//     }
// };
// void
// SegmentGitUntracked::make()
// {
//     GitStatus& status = git_status__;
//     if (status.untracked)
//     {
//         segment.style   =  opt.theme.git_untracked;
//         segment.content =  std::to_string(status.untracked);
//         segment.content += opt.symbols.git_untracked;
//     }
// };
// void
// SegmentGitConflicted::make()
// {
//     GitStatus& status = git_status__;
//     if (status.conflicted)
//     {
//         segment.style   =  opt.theme.git_conflicted;
//         segment.content =  std::to_string(status.conflicted);
//         segment.content += opt.symbols.git_conflicted;
//     }
// };


void
SegmentGit::make()
{
    GitStatus status;
    segment.style = opt.theme.repo_clean;
 
    get_git_status(status);
    if (status.name.empty())
    {
        return;
    }

    segment.content = opt.symbols.git_branch;
    segment.content += ' ';
    segment.content += status.name;

    if (  status.ahead     || status.behind
       || status.staged    || status.not_staged
       || status.untracked || status.conflicted
    ){
        segment.style = opt.theme.repo_dirty;
        if (opt.args.git_mode != "simple")
         return;

        
        if (status.ahead){
            segment.content += ' ';
         segment.content += std::to_string(status.ahead);
            segment.content += opt.symbols.git_ahead;
        }
        if (status.behind){
            segment.content += ' ';
         segment.content += std::to_string(status.behind);
            segment.content += opt.symbols.git_behind;
        }
        if (status.staged){
            segment.content += ' ';
         segment.content += std::to_string(status.staged);
            segment.content += opt.symbols.git_staged;
        }
        if (status.not_staged){
            segment.content += ' ';
         segment.content += std::to_string(status.not_staged);
            segment.content += opt.symbols.git_not_staged;
        }
        if (status.untracked){
            segment.content += ' ';
         segment.content += std::to_string(status.untracked);
            segment.content += opt.symbols.git_untracked;
        }
        if (status.conflicted){
            segment.content += ' ';
         segment.content += std::to_string(status.conflicted);
            segment.content += opt.symbols.git_conflicted;
        }
    }
};


int
get_git_status(GitStatus& status)
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
        return error;

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
        if (error == GIT_ENOTFOUND){
            status.name = "HEAD (no branch)";
        }
        else if (error == GIT_EUNBORNBRANCH) {
            status.name = "HEAD (no commit)";
            return 1;
        }
        else {
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
    }
    else
    {
        status.name = git_reference_shorthand(head);
    }

    // printf("%s\n", git_repository_workdir(repo));
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

         if (s->status & GIT_STATUS_IGNORED)
         {
         }
         else
         if (s->status == GIT_STATUS_CURRENT)
         {
         }
         else
         if (s->status & GIT_STATUS_CONFLICTED)
         {
             status.conflicted ++;
         }
         else
         if (s->status & GIT_STATUS_WT_NEW)
         {
             status.untracked++;
         }
         else
         {
            if (s->status & ( GIT_STATUS_INDEX_NEW      
                            | GIT_STATUS_INDEX_DELETED  
                            | GIT_STATUS_INDEX_RENAMED   
                            | GIT_STATUS_INDEX_MODIFIED 
                            | GIT_STATUS_INDEX_TYPECHANGE))
            {
                status.staged++;
            }
            if (s->status & ( GIT_STATUS_WT_RENAMED
                            | GIT_STATUS_WT_DELETED
                            | GIT_STATUS_WT_MODIFIED
                            | GIT_STATUS_WT_TYPECHANGE))
            {
                status.not_staged++;
            }
         }
    }
    return 0;
}
