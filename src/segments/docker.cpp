#include "modules.hpp"


Module SegmentDocker(const Config& c) {

	Segment segment;

	segment.id      = module::id::docker;
	segment.style   = c.theme.docker;
	segment.content = utils::string::safe(getenv("DOCKER_MACHINE_NAME"));

	if (segment)
	{
		return Module {segment};
	}

	segment.content = utils::string::safe(getenv("DOCKER_HOST"));
	if (segment)
	{
		size_t start = segment.content.find("://");
		size_t stop  = segment.content.find(start, '/');
		segment.content = segment.content.substr(start, stop);
	}

	if (segment)
	{
		return Module {segment};
	}
	return Module {};
}
