#ifndef SEGMENTS_H
#define SEGMENTS_H

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
Segment* segmentGit  (PromptOpt *p);
Segment* segmentGit2 (PromptOpt *p);



#endif
