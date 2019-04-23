#include <filesystem>
#include <cstdlib>
#include "modules.hpp"
#include "utils.hpp"


Module SegmentVenv(const config& c)
{
    char* content_cstr = std::getenv("VIRTUAL_ENV");

    if (!content_cstr)
        return {};
    
    std::string content = c.venv.symbol;
    if (c.venv.verbose)
    {
        content += std::filesystem::path(content_cstr).filename();
    }

    return Module {
        {
            segment::id::venv,
            content,
            c.venv.theme
        }
    };
}
