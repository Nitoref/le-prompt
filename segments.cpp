#include <unordered_map> 
#include "segments.hpp"


SegmentFnPointer getSegmentFn(const char *segmentName)
{
    static const std::unordered_map<std::string, SegmentFnPointer> segmentMap 
    {
        {"user", &segmentHost},
        {"root", &segmentRoot},
        {"host", &segmentUser},
        {"exit", &segmentExit},
        {"pwd" , &segmentPwd},
        {"git" , &segmentGit},
        {"git2", &segmentGit2},
    } ;

    try
    {
        return segmentMap.at(segmentName);
    }
    catch (...)
    {
        return NULL;
    }
}
