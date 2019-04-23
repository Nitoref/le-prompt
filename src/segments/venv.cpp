#include <filesystem>
#include <cstdlib>
#include "modules.hpp"
#include "utils.hpp"


Segment
SegmentVenv(const config& c)
{
    char* content_cstr = std::getenv("VIRTUAL_ENV");

    if (!content_cstr)
        return {};
    
    Segment segment(segment::id::venv);
    segment.theme(c.venv.theme);
    segment.append(c.venv.symbol);
    if (c.venv.verbose)
    {
        segment.append(std::filesystem::path(content_cstr).filename());
    }
    return segment;
}
