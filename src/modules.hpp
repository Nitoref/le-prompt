#ifndef MODULES_H
#define MODULES_H

#include "module.hpp"
#include "config.hpp"

#include <string>
#include <nlohmann/json.hpp>


Module SegmentUser    (const config& c);
Module SegmentRoot    (const config& c);
Module SegmentContext (const config& c);
Module SegmentStatus  (const config& c);
Module SegmentShell   (const config& c);
Module SegmentJobs    (const config& c);
Module SegmentTime    (const config& c);
Module SegmentPerms   (const config& c);
Module SegmentDir     (const config& c);
Module SegmentGit     (const config& c);
Module SegmentSsh     (const config& c);
Module SegmentAws     (const config& c);
Module SegmentDocker  (const config& c);
Module SegmentVirtualEnv (const config& c);


namespace module
{

enum class id: unsigned int {
	user,
	root,
	context,
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
