#ifndef MODULES_H
#define MODULES_H


#include "segment.hpp"
#include "prompt_config.hpp"



Segment SegmentUser (PromptConfig p);
Segment SegmentRoot (PromptConfig p);
Segment SegmentPwd  (PromptConfig p);
Segment SegmentHost (PromptConfig p);
Segment SegmentExit (PromptConfig p);
Segment SegmentJobs (PromptConfig p);
Segment SegmentTime (PromptConfig p);
Segment SegmentGit  (PromptConfig p);



using segment_constructor_t = std::function<Segment(PromptConfig)>;

segment_constructor_t*
get_segment_by_name(std::string str);

#endif
