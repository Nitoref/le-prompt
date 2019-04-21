#include <cstdlib>
#include "modules.hpp"
#include "utils.hpp"


Module SegmentVenv(const config& c)
{
    Segment segment;
    
    segment.content = utils::string(std::getenv("VIRTUAL_ENV"));
    if (segment.content.empty()) {
        segment.content = utils::string(std::getenv("CONDA_ENV_PATH"));
    }
    if (segment.content.empty()) {
        segment.content = utils::string(std::getenv("CONDA_DEFAULT_ENV"));
    }
    segment.style = c.venv.theme;
    segment.id = module::id::venv;
    
    return Module {segment};
}
