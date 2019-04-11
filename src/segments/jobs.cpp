#include "modules.hpp"
#include <unistd.h>
#include "utils.hpp"

Module
SegmentJobs(Config c)
{
	Segment segment;
	
	std::string ppid = std::to_string(getppid());
	int jobs = utils::exec("ps -a -oppid= | grep " + ppid).size() - 1;
	segment.content = jobs ? std::to_string(jobs) : "";
	segment.style = c.theme.jobs;
	segment.id = module::id::perms;
	
	return Module {segment};
}
