#ifndef MODULES_H
#define MODULES_H

#include "module.hpp"
#include "config.hpp"

#include <string>
#include <vector>
#include <functional>
#include <unordered_map>

Module SegmentUser    (const config& c);
Module SegmentHost    (const config& c);
Module SegmentContext (const config& c);
Module SegmentStatus  (const config& c);
Module SegmentRoot    (const config& c);
Module SegmentShell   (const config& c);
Module SegmentJobs    (const config& c);
Module SegmentTime    (const config& c);
Module SegmentPerms   (const config& c);
Module SegmentDir     (const config& c);
Module SegmentHg      (const config& c);
Module SegmentGit     (const config& c);
Module SegmentSsh     (const config& c);
Module SegmentAws     (const config& c);
Module SegmentLoad    (const config& c);
Module SegmentVenv    (const config& c);
Module SegmentDocker  (const config& c);


namespace constructor
{

using string = std::string;
using strvec = std::vector<string>;

using function_t = std::function<Module(const config&)>;
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
get(string str)
{
    if (auto s = functions.find(str); s != functions.end()) {
        return &s->second;
    }
    return nullptr;
};


}

namespace module
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
	path,
	home,
	hg,
	git_branch,
	git_tag,
	git_ahead,
	git_behind,
	git_staged,
	git_notstaged,
	git_untracked,
	git_conflicted,
	git_stash,
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
