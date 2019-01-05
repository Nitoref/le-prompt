#ifndef MODULES_H
#define MODULES_H


#include "threadedSegment.hpp"

struct SegmentUser: public ThreadedSegment{
    using ThreadedSegment::ThreadedSegment;
    Segment* getSegment();
};

struct SegmentRoot: public ThreadedSegment{
    using ThreadedSegment::ThreadedSegment;
    Segment* getSegment();
};

struct SegmentPwd: public ThreadedSegment{
    using ThreadedSegment::ThreadedSegment;
    Segment* getSegment();
};

struct SegmentHost: public ThreadedSegment{
    using ThreadedSegment::ThreadedSegment;
    Segment* getSegment();
};

struct SegmentGit: public ThreadedSegment{
    using ThreadedSegment::ThreadedSegment;
    Segment* getSegment();
};

struct SegmentExit: public ThreadedSegment{
    using ThreadedSegment::ThreadedSegment;
    Segment* getSegment();
};


#endif
