#ifndef THREADED_SEGMENT_H
#define THREADED_SEGMENT_H

#include <thread>

#include "theme.hpp"
#include "segment.hpp"
#include "promptOptions.hpp"


struct ThreadedSegment
{
    PromptOpt   *opt;
    Segment     *segment;
    std::thread thread;


    ThreadedSegment(PromptOpt *opt){
        this->opt = opt;
    };

    Segment* get(){
        if (thread.joinable())
            thread.join();
        return segment;
    }

    virtual
    Segment* getSegment(){
        return NULL;
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

#endif
