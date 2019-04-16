#include "../modules.hpp"
#include "../utils.hpp"
#include <unistd.h>


Module
SegmentJobs(const Config& c)
{
	std::string ppid = std::to_string(getpgid(getppid()));
	int jobs = utils::exec("ps -a -oppid= | grep " + ppid).size() - 1;
	
	if (!jobs)
	{
		return Module {};
	}

	std::string content;
	if (c.args.jobs_count)
	{
		content += std::to_string(jobs);
	}
	content += c.symbols.jobs;
	
	return Module {
		{
			module::id::perms,
			content,
			c.theme.jobs
		}
	};
}
