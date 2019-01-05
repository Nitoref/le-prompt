#ifndef PS1_H
#define PS1_H

#include <unordered_map> 
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "colorutils.hpp"
#include "segment.hpp"
#include "prompt.hpp"

#include "modules.hpp"

struct Prompt {

    std::unordered_map<std::string, ThreadedSegment*> segments;
    std::vector<ThreadedSegment*> threads;
    PromptOpt options;
    int length    =  0;
    int prevColor = -1;
    
    Prompt(PromptOpt options);

    void parseSegments(std::string str);
    void appendSegment(ThreadedSegment *s);
    void printSegment(Segment s);
    void print();
    void reset();

    ThreadedSegment* getSegmentByName(std::string str);
};

#endif
