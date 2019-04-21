#include <cstdlib>
#include "modules.hpp"
#include "utils.hpp"


Module SegmentVenv(const config& c)
{
    std::string content;;
    
    content = utils::string(std::getenv("VIRTUAL_ENV"));
    if (content.empty())
    {
        content = utils::string(std::getenv("CONDA_ENV_PATH"));
    }
    if (content.empty())
    {
        content = utils::string(std::getenv("CONDA_DEFAULT_ENV"));
    }
    
    return Module {
        {
            module::id::venv,
            content,
            c.venv.theme
        }
    };
}
