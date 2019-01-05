#ifndef THREADED_SEGMENT_H
#define THREADED_SEGMENT_H

#include <thread>

#include "theme.hpp"
#include "segment.hpp"
#include "promptOptions.hpp"


struct ThreadedSegment
{
    PromptOpt   *opt;
    Segment     segment;
    std::thread thread;


    // Constructor
    ThreadedSegment(PromptOpt *opt);

    // Returns pointer to segment 
    virtual
    void
    makeSegment();


    // Spawn thread with create()
    void
    init();
    
    // Join thread if joinable
    void
    join();
};



#endif
