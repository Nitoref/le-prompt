#include "modules.hpp"
#include "utils.hpp"
#include <unistd.h>


Segment
SegmentJobs(const config& c)
{
	std::string ppid = std::to_string(getpgid(getppid()));
	int jobs = utils::exec("ps -a -oppid= | grep " + ppid).size() - 1;

	if (!jobs)
	{
		return {};
	}

	Segment segment(segment::id::jobs);
	segment.theme(c.jobs.theme);
	if (c.jobs.count)
	{
		segment.append(std::to_string(jobs));
	}
	segment.append(c.jobs.symbol);
	return segment;
}
