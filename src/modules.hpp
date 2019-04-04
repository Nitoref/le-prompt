#ifndef MODULES_H
#define MODULES_H


#include "threadedSegment.hpp"


struct SegmentUser: public ThreadedSegment{
    using ThreadedSegment::ThreadedSegment;
    void make();
};

struct SegmentRoot: public ThreadedSegment{
    using ThreadedSegment::ThreadedSegment;
    void make();
};

struct SegmentPwd: public ThreadedSegment{
    using ThreadedSegment::ThreadedSegment;
    void make();
};

struct SegmentHost: public ThreadedSegment{
    using ThreadedSegment::ThreadedSegment;
    void make();
};

struct SegmentGit: public ThreadedSegment{
    using ThreadedSegment::ThreadedSegment;
    void make();
};

struct SegmentExit: public ThreadedSegment{
    using ThreadedSegment::ThreadedSegment;
    void make();
};

struct SegmentNewline: public ThreadedSegment{
    using ThreadedSegment::ThreadedSegment;
    void make();
};


#endif
