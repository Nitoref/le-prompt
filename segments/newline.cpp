#include <string.h>
#include "../modules.hpp"

void
SegmentNewline::make()
{
    segment.content = " ";
    segment.style   = {-1, -1};
}
