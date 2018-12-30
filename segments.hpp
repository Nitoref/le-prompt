#ifndef SEGMENTS_H
#define SEGMENTS_H

#include <map>
#include "theme.hpp"
#include "segment.hpp"
#include "promptOptions.hpp"


typedef Segment*(*SegmentFnPointer)(PromptOpt*);
SegmentFnPointer getSegmentFn(const char* segmentName);

Segment* segmentHost (PromptOpt *p);
Segment* segmentUser (PromptOpt *p);
Segment* segmentPwd  (PromptOpt *p);
Segment* segmentRoot (PromptOpt *p);
Segment* segmentExit (PromptOpt *p);

static const std::map<std::string, SegmentFnPointer> segmentMap 
{
    {"user", &segmentHost},
    {"root", &segmentRoot},
    {"host", &segmentUser},
    {"exit", &segmentExit},
    {"pwd" , &segmentPwd},
} ;


#endif
