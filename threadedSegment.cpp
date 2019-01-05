#include "threadedSegment.hpp"


ThreadedSegment::ThreadedSegment(PromptOpt *opt){
    this->opt = opt;
}


Segment*
ThreadedSegment::makeSegment(){
    return NULL;
}

void
ThreadedSegment::init(){
    if (!thread.joinable())
        thread = std::thread([&]{
            create();
        });
}

void
ThreadedSegment::create()
{
    segment = makeSegment();
}

void
ThreadedSegment::join()
{
    if (thread.joinable())
        thread.join();
}

Segment*
ThreadedSegment::get()
{
    join();
    return segment;
}
