#include <string.h>
#include "../modules.hpp"

void
SegmentNewline::make()
{
    segment.content = strdup("\n");
    segment.style   = Style();
}
