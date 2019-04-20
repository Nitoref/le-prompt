#include "modules.hpp"
#include "utils.hpp"
#include <regex>

Module SegmentDocker(const config& c) {

	Segment segment;

	segment.id      = module::id::docker;
	segment.style   = c.docker.theme;
	segment.content = utils::string(getenv("DOCKER_MACHINE_NAME"));

	if (segment)
	{
		return Module {segment};
	}

	segment.content = utils::string(getenv("DOCKER_HOST"));
	if (!segment)
	{
		return Module {};
	}

	// https://tools.ietf.org/html/rfc3986#appendix-B
	std::regex r (R"(^(([^:/?#]+):)?(//([^/?#]*))?([^?#]*)(\?([^#]*))?(#(.*))?)");
	segment.content = std::regex_replace(segment.content, r, "$4");

	if (segment)
	{
		return Module {segment};
	}
	return Module {};
}
