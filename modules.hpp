#ifndef MODULES_H
#define MODULES_H


#include "threadedSegment.hpp"

struct SegmentUser: public ThreadedSegment{
    using ThreadedSegment::ThreadedSegment;
    void makeSegment();
};

struct SegmentRoot: public ThreadedSegment{
    using ThreadedSegment::ThreadedSegment;
    void makeSegment();
};

struct SegmentPwd: public ThreadedSegment{
    using ThreadedSegment::ThreadedSegment;
    void makeSegment();
};

struct SegmentHost: public ThreadedSegment{
    using ThreadedSegment::ThreadedSegment;
    void makeSegment();
};

struct SegmentGit: public ThreadedSegment{
    using ThreadedSegment::ThreadedSegment;
    void makeSegment();
};

struct SegmentExit: public ThreadedSegment{
    using ThreadedSegment::ThreadedSegment;
    void makeSegment();
};


#endif
