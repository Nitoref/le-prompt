#include <cstdlib>
#include "segments.hpp"
#include "utils.hpp"

Segment SegmentSsh(PromptConfig p)
{
    Segment segment;
    segment.content = utils::string::safe(getenv("SSH_CLIENT"));
    segment.style = p.theme.ssh;
    return segment;
}
