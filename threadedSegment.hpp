#ifndef THREADED_SEGMENT_H
#define THREADED_SEGMENT_H

#include <thread>

#include "segment.hpp"
#include "promptOptions.hpp"


struct ThreadedSegment
{
    // Pointer to father's options
    PromptOpt   &opt;
    // Segment 
    Segment     segment;
    // Thread
    std::thread thread;

    // Constructor
    ThreadedSegment(PromptOpt &opt);

    // Assign content and style to segment
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
