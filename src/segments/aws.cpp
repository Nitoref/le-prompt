#include <cstdlib>
#include "segments.hpp"
#include "utils.hpp"


MultiSegment SegmentAws(PromptConfig p)
{
	Segment segment;
    segment.content = utils::string::safe(getenv("AWS_PROFILE"));
    segment.style = p.theme.aws;
    return {segment};
}
