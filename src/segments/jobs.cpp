#include "modules.hpp"
#include <unistd.h>
#include "utils.hpp"

void
SegmentJobs::make()
{
	std::string ppid = std::to_string(getppid());
	int jobs = utils::exec("ps -a -oppid= | grep " + ppid).size() - 1;
	segment.content = jobs ? std::to_string(jobs) : "";
	segment.style = opt.theme.jobs;
}
