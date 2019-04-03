#ifndef THREADED_SEGMENT_H
#define THREADED_SEGMENT_H

#include <thread>

#include "segment.hpp"
#include "prompt_config.hpp"


struct ThreadedSegment
{
    PromptConfig   &opt;
    Segment     segment;
    std::thread thread;

    // Initialize with prompt options
    ThreadedSegment(PromptConfig &opt):opt(opt)
    {};

    // Get content and style
    virtual void make()
    {};

    // Spawn thread
    void init()
    {
        if (!thread.joinable()){
            thread = std::thread([&]{
                make();
            });
        }
    }

    // Join thread
    void join()
    {
        if (thread.joinable())
            thread.join();
    }
};


#endif
