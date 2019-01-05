#include "threadedSegment.hpp"


ThreadedSegment::ThreadedSegment(PromptOpt *opt){
    this->opt = opt;
}


void
ThreadedSegment::makeSegment(){
    ;
}

void
ThreadedSegment::init(){
    if (!thread.joinable())
        thread = std::thread([&]{
            makeSegment();
        });
}


void
ThreadedSegment::join()
{
    if (thread.joinable())
        thread.join();
}
