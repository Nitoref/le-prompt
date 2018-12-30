#ifndef PS1_H
#define PS1_H

#include <iostream>
#include <vector>
#include <thread>
#include <future>

#include "segments.hpp"
#include "prompt.hpp"

#define DEFAULT '9'
#define _STD_BG '4'
#define _STD_FG '3'
#define _256_BG "48;5;"
#define _256_FG "38;5;"
#define    _ESC "\\[\\e["
#define    _CSE "m\\]"


struct Prompt {

    std::vector<std::future<Segment*>> segments;
    PromptOpt options;
    
    Prompt(PromptOpt options):options(options)
    {}

    void appendSegment(const char *name){
        if (SegmentFnPointer fn = getSegmentFn(name))
            segments.push_back(std::async(*fn, &options));
    };

    void print();
};



void setBg(int value){
    printf("%s%s%d%s",_ESC, _256_BG, value, _CSE);
}

void setFg(int value){
    printf("%s%s%d%s",_ESC, _256_FG, value, _CSE);
}

void resetBg(){
    printf("%s%c%d%s",_ESC, _STD_BG, DEFAULT, _CSE);
}

void resetFg(){
    printf("%s%c%d%s",_ESC, _STD_FG, DEFAULT, _CSE);
}

void resetStyle(){
    printf("%s%c%s",_ESC, '0', _CSE);
}


void Prompt::print()
{
    static int cut;
    static int length;
    static int prevColor = -1;

    for (auto &segment : segments){
        if (Segment *s = segment.get()){
            if (s -> style.bg == prevColor)
            {
                length += strlen(options.symbols->SeparatorThin);
                setFg(s -> style.fg);
                printf("%s", options.symbols->SeparatorThin);
            }
            else
            if (prevColor != -1)
            {
                length += strlen(options.symbols->Separator);
                setBg(s -> style.bg);
                setFg(prevColor);
                printf("%s", options.symbols->Separator);
            }

            setBg(s -> style.bg);
            setFg(s -> style.fg);
            printf(" %s ",s -> content);
            length += strlen(s -> content) + 2;
            prevColor = s -> style.bg;
        }
    }
    resetStyle();
    setFg(prevColor);
    printf("%s  ", options.symbols->Separator);
}
#endif
