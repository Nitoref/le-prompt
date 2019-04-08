#include <cstdlib>
#include "segments.hpp"
#include "utils.hpp"


Segment SegmentVirtualEnv(PromptConfig p)
{
    Segment segment;
    
    segment.content = utils::string::safe(getenv("VIRTUAL_ENV"));
    if (segment.content.empty()) {
        segment.content = utils::string::safe(getenv("CONDA_ENV_PATH"));
    }
    if (segment.content.empty()) {
        segment.content = utils::string::safe(getenv("CONDA_DEFAULT_ENV"));
    }
    segment.style = p.theme.virtual_env;
    
    return segment;
}
