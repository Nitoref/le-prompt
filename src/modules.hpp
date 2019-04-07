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

struct SegmentExit: public ThreadedSegment{
    using ThreadedSegment::ThreadedSegment;
    void make();
};

struct SegmentJobs: public ThreadedSegment{
    using ThreadedSegment::ThreadedSegment;
    void make();
};

struct SegmentTime: public ThreadedSegment{
    using ThreadedSegment::ThreadedSegment;
    void make();
};






struct SegmentGit: public ThreadedSegment{
    using ThreadedSegment::ThreadedSegment;
    void make();
};
// struct SegmentGitName: public ThreadedSegment{
//     using ThreadedSegment::ThreadedSegment;
//     void make();
// };
// struct SegmentGitAhead: public ThreadedSegment{
//     using ThreadedSegment::ThreadedSegment;
//     void make();
// };
// struct SegmentGitBehind: public ThreadedSegment{
//     using ThreadedSegment::ThreadedSegment;
//     void make();
// };
// struct SegmentGitStaged: public ThreadedSegment{
//     using ThreadedSegment::ThreadedSegment;
//     void make();
// };
// struct SegmentGitNotStaged: public ThreadedSegment{
//     using ThreadedSegment::ThreadedSegment;
//     void make();
// };
// struct SegmentGitUntracked: public ThreadedSegment{
//     using ThreadedSegment::ThreadedSegment;
//     void make();
// };
// struct SegmentGitConflicted: public ThreadedSegment{
//     using ThreadedSegment::ThreadedSegment;
//     void make();
// };


#endif
