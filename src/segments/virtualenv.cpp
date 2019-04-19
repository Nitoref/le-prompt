#include <cstdlib>
#include "../modules.hpp"
#include "../utils.hpp"


Module SegmentVirtualEnv(const config& c)
{
    Segment segment;
    
    segment.content = utils::string(getenv("VIRTUAL_ENV"));
    if (segment.content.empty()) {
        segment.content = utils::string(getenv("CONDA_ENV_PATH"));
    }
    if (segment.content.empty()) {
        segment.content = utils::string(getenv("CONDA_DEFAULT_ENV"));
    }
    segment.style = c.virtual_env.theme;
    segment.id = module::id::virtual_env;
    
    return Module {segment};
}
