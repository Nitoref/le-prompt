#ifndef GIT_H
#define GIT_H

#include "segments.hpp"
#include <thread>


struct segmentGit
{
    struct RepoStats
    {
        size_t ahead;
        size_t behind;
        size_t staged;
        size_t notStaged;
        size_t untracked;
        size_t conflicted;
    };

    PromptOpt   *p;
    Segment     *segment;
    std::thread thread;

    static RepoStats stats;
    static  char* repoName;

    segmentGit(PromptOpt *p):p(p)
    {
    };

    Segment* getSegment(){
        return NULL;
    }

    Segment* get(){
        if (thread.joinable())
            thread.join();
        return segment;
    }

    void set(){
        segment = getSegment();
    }

    void init()
    {
        if (!thread.joinable())
            thread = std::thread([&]{
                set();
            });
    }
};

// struct segmentGit



#endif
