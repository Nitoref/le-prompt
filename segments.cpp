#include "segments.hpp"


SegmentFnPointer getSegmentFn(const char *segmentName)
{
    try {
        return segmentMap.at(segmentName);
    } catch (...) {
        return NULL;
    }
}
