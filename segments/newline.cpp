#include <string.h>
#include "../modules.hpp"

void
SegmentNewline::make()
{
    segment.content = strdup("");
    segment.style   = Style(-1, -1);
}
