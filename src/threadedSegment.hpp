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

    ThreadedSegment(PromptConfig &opt):opt(opt)
    {};

    virtual void make()
    {};

    void init()
    {
        if (!thread.joinable()){
            thread = std::thread([&]{
                make();
            });
        }
    }

    void join()
    {
        if (thread.joinable())
            thread.join();
    }
};


#endif
