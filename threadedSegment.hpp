#ifndef THREADED_SEGMENT_H
#define THREADED_SEGMENT_H

#include <thread>

#include "segment.hpp"
#include "promptOptions.hpp"


struct ThreadedSegment
{
    PromptOpt   &opt;
    Segment     segment;
    std::thread thread;

    // Initialize with prompt options
    ThreadedSegment(PromptOpt &opt):
    opt(opt){};

    // Get content and style
    virtual
    void
    make()
    {};

    // Spawn thread with create()
    void
    init()
    {
        if (!thread.joinable()){
            thread = std::thread([&]{
                make();
            });
        }
    }

    // Join thread if joinable
    void
    join()
    {
        if (thread.joinable())
            thread.join();
    }
};


#endif
