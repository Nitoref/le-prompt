#include "modules.hpp"
#include "utils.hpp"
#include <unistd.h>


Module
SegmentJobs(const config& c)
{
	std::string ppid = std::to_string(getpgid(getppid()));
	int jobs = utils::exec("ps -a -oppid= | grep " + ppid).size() - 1;

	if (!jobs)
	{
		return {};
	}

	std::string content;
	if (c.jobs.count)
	{
		content += std::to_string(jobs);
	}
	content += c.jobs.symbol;
	
	return Module {
		{
			segment::id::jobs,
			content,
			c.jobs.theme
		}
	};
}
