#ifndef MODULES_H
#define MODULES_H

#include "segment.hpp"
#include "config.hpp"

#include <string>
#include <vector>
#include <functional>
#include <unordered_map>

Segment SegmentUser    (const config& c);
Segment SegmentHost    (const config& c);
Segment SegmentContext (const config& c);
Segment SegmentStatus  (const config& c);
Segment SegmentRoot    (const config& c);
Segment SegmentShell   (const config& c);
Segment SegmentJobs    (const config& c);
Segment SegmentTime    (const config& c);
Segment SegmentPerms   (const config& c);
Segment SegmentDir     (const config& c);
Segment SegmentHg      (const config& c);
Segment SegmentGit     (const config& c);
Segment SegmentSsh     (const config& c);
Segment SegmentAws     (const config& c);
Segment SegmentLoad    (const config& c);
Segment SegmentVenv    (const config& c);
Segment SegmentDocker  (const config& c);


namespace constructor
{

using string = std::string;
using strvec = std::vector<string>;

using function_t = std::function<Segment(const config&)>;
using map_t      = std::unordered_map<string, function_t>;

inline map_t functions = {
    {"user",   &SegmentUser},
    {"host",   &SegmentHost},
    {"context",&SegmentContext},
    {"status", &SegmentStatus},
    {"root",   &SegmentRoot},
    {"shell",  &SegmentShell},
    {"jobs",   &SegmentJobs},
    {"time",   &SegmentTime},
    {"perms",  &SegmentPerms},
    {"dir",    &SegmentDir},
    {"git",    &SegmentGit},
    {"hg",     &SegmentHg},
    {"ssh",    &SegmentSsh},
    {"aws",    &SegmentAws},
    {"load",   &SegmentLoad},
    {"venv",   &SegmentVenv},
    {"docker", &SegmentDocker}
};

inline function_t*
get(string str) {
    if (auto s = functions.find(str); s != functions.end()) {
        return &s->second;
    }
    return nullptr;
}


}

namespace segment
{

enum class id: unsigned int {
	user,
	host,
	context,
	status,
	root,
	shell,
	jobs,
	time,
	perms,
	dir,
	hg,
	git,
	ssh,
	aws,
	load,
	venv,
	docker,
	extension,
	__count
};

}

#endif
