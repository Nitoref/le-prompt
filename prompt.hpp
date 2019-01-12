#ifndef PS1_H
#define PS1_H

#include <unordered_map> 
#include <vector>

#include "colorutils.hpp"
#include "modules.hpp"

struct Prompt {

    std::unordered_map<std::string, ThreadedSegment*> segments;
    std::vector<ThreadedSegment*> threads;
    std::vector<ThreadedSegment*> rightThreads;
    
    PromptOpt options;
    ColorPrinter printer;
    size_t length =  0;
    int prevColor = -1;
    

    Prompt(PromptOpt options);
    void parseLeftSegments(std::vector<std::string> segments);
    void parseRightSegments(std::vector<std::string> segments);
    void parseLeftSegments();
    void parseRightSegments();
    
    void printSegment(Segment s);
    void printRSegment(Segment s);
    void printLeft();
    void printRight();
    void reset();

    ThreadedSegment* getSegmentByName(std::string str);
};

#endif
