#ifndef GIT_H
#define GIT_H

#include "threadedSegment.hpp"


struct SegmentGit: public ThreadedSegment
{
    using ThreadedSegment::ThreadedSegment;

    struct RepoStats
    {
        size_t ahead      = 0;
        size_t behind     = 0;
        size_t staged     = 0;
        size_t notStaged  = 0;
        size_t untracked  = 0;
        size_t conflicted = 0;
    };

    static PromptOpt  *opt;
    static RepoStats stats;
    static char* repoName;

    Segment* getSegment(){
        return NULL;
    }
};

#endif
