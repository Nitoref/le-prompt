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

    std::vector<int> segments;
    PromptOpt options;
    int length    =  0;
    int prevColor = -1;
    
    Prompt(PromptOpt options):options(options){
        segments.reserve(10);
            std::unordered_map<int, Segment*> s (
                {1, new SegmentUser(&this->options)},
                {2, new SegmentRoot(&this->options)},
                {3, new SegmentPwd(&this->options)},
                {4, new SegmentExit(&this->options)},
                {5, new SegmentGit(&this->options)},
                {6, new SegmentHost(&this->options)}
            );
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
        // TODO
        continue;
}

void Prompt::appendSegment(const char *str){
    // TODO
};


void Prompt::print()
{
    for (auto &segment : segments){
        // TODO
        continue;
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
