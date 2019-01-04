#ifndef PS1_H
#define PS1_H

#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <string>
#include <sstream>

#include "colorutils.hpp"
#include "segments.hpp"
#include "prompt.hpp"


struct Prompt {

    std::vector<std::future<Segment*>> segments;
    PromptOpt options;
    int length    =  0;
    int prevColor = -1;
    
    Prompt(PromptOpt options):options(options){
        segments.reserve(10);
    }

    void parseSegments(const char *name);
    void appendSegment(const char *name);
    void printSegment(Segment s);
    void print();
    void reset();
};


void Prompt::parseSegments(const char *str)
{
    std::string buff;
    std::stringstream ss(str);
    while(std::getline(ss, buff, ','))
        if (SegmentFnPointer fn = getSegmentFn(buff.c_str()))
            segments.push_back(std::async(*fn, &options));
}

void Prompt::appendSegment(const char *str){
    if (SegmentFnPointer fn = getSegmentFn(str))
        segments.push_back(std::async(*fn, &options));
};


void Prompt::print()
{
    for (auto &segment : segments){
        if (Segment *s = segment.get()){
            printSegment(*s);
        }
    }
    reset();
}

void Prompt::printSegment(Segment s)
{
    if (s.style.bg == prevColor)
    {
        length += strlen(options.symbols->SeparatorThin);
        setFg(s.style.fg);
        printf("%s", options.symbols->SeparatorThin);
    }
    else
    if (prevColor != -1)
    {
        length += strlen(options.symbols->Separator);
        setBg(s.style.bg);
        setFg(prevColor);
        printf("%s", options.symbols->Separator);
    }
    setBg(s.style.bg);
    setFg(s.style.fg);
    printf(" %s ",s.content);
    length += strlen(s.content) + 2;
    prevColor = s.style.bg;
}

void Prompt::reset(){
    resetStyle();
    setFg(prevColor);
    printf("%s  ", options.symbols->Separator);
    resetStyle();
}
#endif
