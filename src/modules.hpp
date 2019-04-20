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
Module SegmentDir     (const config& c);
Module SegmentGit     (const config& c);
Module SegmentPerms   (const config& c);
Module SegmentSsh     (const config& c);
Module SegmentAws     (const config& c);
Module SegmentDocker  (const config& c);
Module SegmentVirtualEnv (const config& c);


namespace constructor
{

using string = std::string;
using strvec = std::vector<string>;

using function_t = std::function<Module(const config&)>;
using map_t      = std::unordered_map<string, function_t>;

inline map_t map = {
    {"user",   &SegmentUser},
    {"host",   &SegmentHost},
    {"context",&SegmentContext},
    {"status", &SegmentStatus},
    {"root",   &SegmentRoot},
    {"shell",  &SegmentShell},
    {"jobs",   &SegmentJobs},
    {"time",   &SegmentTime},
    {"dir",    &SegmentDir},
    {"git",    &SegmentGit},
    {"perms",  &SegmentPerms},
    {"ssh",    &SegmentSsh},
    {"aws",    &SegmentAws},
    {"docker", &SegmentDocker},
    {"venv",   &SegmentVirtualEnv}
};

inline function_t*
get(string str)
{
    if (auto s = map.find(str); s != map.end()) {
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
	git_branch,
	git_ahead,
	git_behind,
	git_staged,
	git_nstaged,
	git_untracked,
	git_conflicted,
	git_stash,
	ssh,
	aws,
	docker,
	virtual_env,
	extension,
	__count
};

}

#endif
