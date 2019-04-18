#ifndef MODULES_H
#define MODULES_H

#include "module.hpp"
#include "config.hpp"

#include <string>
#include <nlohmann/json.hpp>


Module SegmentUser   (const Config& c);
Module SegmentRoot   (const Config& c);
Module SegmentHost   (const Config& c);
Module SegmentStatus (const Config& c);
Module SegmentShell  (const Config& c);
Module SegmentJobs   (const Config& c);
Module SegmentTime   (const Config& c);
Module SegmentPerms  (const Config& c);
Module SegmentDir    (const Config& c);
Module SegmentGit    (const Config& c);
Module SegmentSsh    (const Config& c);
Module SegmentAws    (const Config& c);
Module SegmentDocker (const Config& c);
Module SegmentVirtualEnv (const Config& c);


namespace module
{

enum class id: unsigned int {
	user,
	root,
	host,
	status,
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
