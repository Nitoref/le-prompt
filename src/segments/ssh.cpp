#include <cstdlib>
#include "modules.hpp"
#include "utils.hpp"

Module SegmentSsh(Config c)
{
    Segment segment;
    segment.content = utils::string::safe(getenv("SSH_CLIENT"));
    segment.style = c.theme.ssh;
    segment.id = module::id::ssh;
    return Module {segment};
}
