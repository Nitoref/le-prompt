#include <string.h>
#include <stdio.h>
#ifdef _WIN32
# include <Windows.h>
#else
# include <unistd.h>
#endif
#include "../modules.hpp"
#include "git2.hpp"



SegmentGit2::RepoStats SegmentGit2::stats;
bool SegmentGit2::set;
char *SegmentGit2::branchName;
char *SegmentGit2::repoName;
git_repository *SegmentGit2::repo;
git_reference *SegmentGit2::head;

int
SegmentGit2::get_git_status()
{
    set = true;

    git_status_list *status;
    git_status_options opt = GIT_STATUS_OPTIONS_INIT;
 
    git_libgit2_init();

    opt.show  = GIT_STATUS_SHOW_INDEX_AND_WORKDIR;

    opt.flags = \
        GIT_STATUS_OPT_INCLUDE_UNTRACKED        |
        GIT_STATUS_OPT_RENAMES_INDEX_TO_WORKDIR |
        GIT_STATUS_OPT_EXCLUDE_SUBMODULES       |
        GIT_STATUS_OPT_NO_REFRESH               |
        GIT_STATUS_OPT_SORT_CASE_SENSITIVELY;

    if (git_repository_open_ext(&repo, ".", 0, NULL))
        return 1;
    if (get_branch_name())
        return 1; 
    if (get_ahead_behind())
        return 1;
    if (git_repository_is_bare(repo))
        return 0;
    if (git_status_list_new(&status, repo, &opt))
        return 1;
    if (get_stats(status))
        return 1;
 
    git_status_list_free(status);
    git_repository_free(repo);
    git_libgit2_shutdown();
    return 0;
}


int 
SegmentGit2::get_ahead_behind()
{
    git_reference *upstream = NULL;

    int error = git_branch_upstream(&upstream, head);
    if (error)
    {
        return error;
    }

    git_graph_ahead_behind(
        &(stats.ahead), &(stats.behind),
        repo,
        git_reference_target(head),
        git_reference_target(upstream)
    );
    return 0;
}


int
SegmentGit2::get_branch_name()
{    
    git_reference *head     = NULL;

    int error = git_repository_head(&head, repo);
    if (error)
    {
        if (error == GIT_ENOTFOUND ||
            error == GIT_EUNBORNBRANCH
        ){
            branchName = strdup("HEAD (no branch)");
        }
        else
        {
            return 1;
        }
    }

    if (git_repository_head_detached(repo))
    {
        branchName = (char*)malloc(8*sizeof(char));
        git_oid_tostr(
            branchName, sizeof(branchName), 
            git_reference_target(head)
        );
    }
    else
    {
        branchName = strdup(git_reference_shorthand(head));
    }

    // printf("%s\n", git_repository_workdir(repo));
    git_reference_free(head);
    return 0;
}


int
SegmentGit2::get_stats(git_status_list *status)
{
    size_t maxi = git_status_list_entrycount(status);
    const git_status_entry *s;

    for (size_t i = 0; i < maxi; ++i) {
        s = git_status_byindex(status, i);

         if (s->status & GIT_STATUS_IGNORED){
         }
         else
         if (s->status == GIT_STATUS_CURRENT){
         }
         else
         if (s->status & GIT_STATUS_CONFLICTED){
             stats.conflicted ++;
         }
         else
         if (s->status & GIT_STATUS_WT_NEW){
             stats.untracked++;
         }
         else
         {
            if (s->status & ( GIT_STATUS_INDEX_NEW      
                            | GIT_STATUS_INDEX_DELETED  
                            | GIT_STATUS_INDEX_RENAMED   
                            | GIT_STATUS_INDEX_MODIFIED 
                            | GIT_STATUS_INDEX_TYPECHANGE))
            {
                stats.staged++;
            }
            if (s->status & ( GIT_STATUS_WT_RENAMED
                            | GIT_STATUS_WT_DELETED
                            | GIT_STATUS_WT_MODIFIED
                            | GIT_STATUS_WT_TYPECHANGE))
            {
                stats.notStaged++;
            }
         }
    }
    return 0;
}
