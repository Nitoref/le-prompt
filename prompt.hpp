#ifndef PS1_H
#define PS1_H

#include <unordered_map> 
#include <vector>

#include "modules.hpp"

struct Prompt {

    std::unordered_map<std::string, ThreadedSegment*> segments;
    std::vector<ThreadedSegment*> threads;
    PromptOpt options;
    int length    =  0;
    int prevColor = -1;
    
    Prompt(PromptOpt options);

    void parseSegments();
    void appendSegment(ThreadedSegment *s);
    void printSegment(Segment s);
    void print();
    void reset();

    ThreadedSegment* getSegmentByName(std::string str);
};

#endif
