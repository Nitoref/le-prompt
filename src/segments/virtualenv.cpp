#include <cstdlib>
#include "../modules.hpp"
#include "../utils.hpp"


Module SegmentVirtualEnv(const Config& c)
{
    Segment segment;
    
    segment.content = utils::string::safe(getenv("VIRTUAL_ENV"));
    if (segment.content.empty()) {
        segment.content = utils::string::safe(getenv("CONDA_ENV_PATH"));
    }
    if (segment.content.empty()) {
        segment.content = utils::string::safe(getenv("CONDA_DEFAULT_ENV"));
    }
    segment.style = c.theme.virtual_env;
    segment.id = module::id::virtual_env;
    
    return Module {segment};
}
