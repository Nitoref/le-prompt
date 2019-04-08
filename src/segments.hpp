#ifndef MODULES_H
#define MODULES_H


#include "segment.hpp"
#include "prompt_config.hpp"



MultiSegment SegmentUser (PromptConfig p);
MultiSegment SegmentRoot (PromptConfig p);
MultiSegment SegmentPwd  (PromptConfig p);
MultiSegment SegmentHost (PromptConfig p);
MultiSegment SegmentExit (PromptConfig p);
MultiSegment SegmentJobs (PromptConfig p);
MultiSegment SegmentTime (PromptConfig p);
MultiSegment SegmentGit  (PromptConfig p);
MultiSegment SegmentPerms(PromptConfig p);
MultiSegment SegmentSsh  (PromptConfig p);
MultiSegment SegmentAws  (PromptConfig p);
MultiSegment SegmentVirtualEnv(PromptConfig p);


#endif
