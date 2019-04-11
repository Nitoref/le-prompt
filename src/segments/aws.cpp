#include <cstdlib>
#include "modules.hpp"
#include "utils.hpp"


Module SegmentAws(Config c)
{
	Segment segment;
    segment.content = utils::string::safe(getenv("AWS_PROFILE"));
    segment.style   = c.theme.aws;
    segment.id      = module::id::aws;
    return Module {segment};
}
