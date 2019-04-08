#include <unordered_map>
#include "segments.hpp"


segment_constructor_t*
get_segment_by_name(std::string str)
{
	static
	std::unordered_map<std::string, segment_constructor_t>
	segments_map_ {
        {"user",  SegmentUser},
        {"root",  SegmentRoot},
        {"pwd",   SegmentPwd},
        {"exit",  SegmentExit},
        {"host",  SegmentHost},
        {"jobs",  SegmentJobs},
        {"git",   SegmentGit},
        {"time",  SegmentTime},
        {"perms", SegmentPerms},
        {"ssh",   SegmentSsh},
        {"aws",   SegmentAws},
        {"virtualenv", SegmentVirtualEnv}
    };
    if (auto s = segments_map_.find(str); s != segments_map_.end())
        return &s->second;
    return nullptr;
}
