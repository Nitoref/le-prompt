#include <git2.h>
#include <string.h>
#include <stdio.h>
#ifdef _WIN32
# include <Windows.h>
#else
# include <unistd.h>
#endif
#include "../modules.hpp"

struct RepoStats
{
    size_t ahead;
    size_t behind;
    size_t staged;
    size_t notStaged;
    size_t untracked;
    size_t conflicted;
};

static int get_git_status(char **branchName, RepoStats *stats);
static int get_stats(RepoStats *stats, git_repository *repo, git_status_list *status);
static int get_ahead_behind(RepoStats *stats, git_repository *repo, git_reference *head);
static int get_name(char **branch, RepoStats *stats, git_repository *repo);




Segment*
SegmentGit::getSegment()
{
    RepoStats stats;
    char *branchName = NULL;
    Segment *segment;
    Style      style = opt->theme->RepoClean;
 
    get_git_status(&branchName, &stats);
    if (branchName == NULL)
    {
        return NULL;
    }

    segment = new Segment(branchName, style);

    if (  stats.ahead
       || stats.behind
       || stats.staged
       || stats.notStaged
       || stats.untracked
       || stats.conflicted)
    {
        segment -> style = opt -> theme -> RepoDirty;
        if(!strcmp(opt->args->GitMode, "compact"))
        {
            char *statsStr = (char*)malloc(4 * 6 + 2);
            strcpy(statsStr, " ");
            if (stats.ahead)
            {
                strcat(statsStr, opt->symbols->GitAhead);
            }
            if (stats.behind)
            {
                strcat(statsStr, opt->symbols->GitBehind);
            }
            if (stats.staged)
            {
                strcat(statsStr, opt->symbols->GitStaged);
            }
            if (stats.notStaged)
            {
                strcat(statsStr, opt->symbols->GitNotStaged);
            }
            if (stats.untracked)
            {
                strcat(statsStr, opt->symbols->GitUntracked);
            }
            if (stats.conflicted)
            {
                strcat(statsStr, opt->symbols->GitConflicted);
            }

            if (strlen(statsStr) > 1)
            {
                branchName = (char*)realloc(branchName, strlen(branchName) + strlen(statsStr) + 1);
                strcat(branchName, statsStr);
            }
        }
    }
    return segment;
};

static
int
get_git_status(char **branchName, RepoStats *stats)
{
    git_repository  *repo    = NULL;
    git_status_list *status;
    git_status_options statusopt = GIT_STATUS_OPTIONS_INIT;
 
    git_libgit2_init();

    statusopt.show  = GIT_STATUS_SHOW_INDEX_AND_WORKDIR;

    statusopt.flags = GIT_STATUS_OPT_INCLUDE_UNTRACKED 
                    | GIT_STATUS_OPT_RENAMES_INDEX_TO_WORKDIR
                    | GIT_STATUS_OPT_EXCLUDE_SUBMODULES
                    | GIT_STATUS_OPT_NO_REFRESH
                    | GIT_STATUS_OPT_SORT_CASE_SENSITIVELY;

    if (git_repository_open_ext(&repo, ".", 0, NULL))
    {
        return 1;
    }
    
    if (get_name(branchName, stats, repo))
    {
        return 1; 
    }

    if (git_repository_is_bare(repo))
    {
        return 0; // cannot status on bare repo
    }

    if (git_status_list_new(&status, repo, &statusopt))
    {
        return 1;
    }

    if (get_stats(stats, repo, status))
    {
        return 1;
    }
 
    git_status_list_free(status);
    git_repository_free(repo);
    git_libgit2_shutdown();
    return 0;
}

static 
int 
get_ahead_behind(RepoStats *stats, git_repository *repo, git_reference *head)
{
    int    error;
    size_t ahead;
    size_t behind;
    git_reference *upstream = NULL;

    error = git_branch_upstream(&upstream, head);
    if (error)
        return error;

    git_graph_ahead_behind(
        &(stats -> ahead), &(stats -> behind),
        repo,
        git_reference_target(head),
        git_reference_target(upstream)
    );
    return 0;
}


static
int
get_name(char **branch, RepoStats *stats, git_repository *repo)
{    
    git_reference *head     = NULL;

    int error = git_repository_head(&head, repo);
    if (error)
    {
        if (error == GIT_ENOTFOUND || error == GIT_EUNBORNBRANCH)
            *branch = strdup("HEAD (no branch)");
        else
            return 1;
    }

    if (git_repository_head_detached(repo))
    {
        *branch = (char*)malloc(8*sizeof(char));
        git_oid_tostr(*branch, sizeof(*branch), git_reference_target(head));
    }
    else
    {
        *branch = strdup(git_reference_shorthand(head));
    }

    get_ahead_behind(stats, repo, head);

    // printf("%s\n", git_repository_workdir(repo));
    git_reference_free(head);
    return 0;
}



static
int
get_stats(RepoStats *stats, git_repository *repo, git_status_list *status)
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
             stats -> conflicted ++;
         }
         else
         if (s->status & GIT_STATUS_WT_NEW){
             stats -> untracked++;
             // printf("untracked : %s\n", s->index_to_workdir->new_file.path);
         }
         else
         {
            if (s->status & ( GIT_STATUS_INDEX_NEW      
                            | GIT_STATUS_INDEX_DELETED  
                            | GIT_STATUS_INDEX_RENAMED   
                            | GIT_STATUS_INDEX_MODIFIED 
                            | GIT_STATUS_INDEX_TYPECHANGE))
            {
                stats -> staged++;
            }
            if (s->status & ( GIT_STATUS_WT_RENAMED
                            | GIT_STATUS_WT_DELETED
                            | GIT_STATUS_WT_MODIFIED
                            | GIT_STATUS_WT_TYPECHANGE))
            {
                stats -> notStaged++;
            }
         }
    }
    return 0;
}
