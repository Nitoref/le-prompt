#include "modules.hpp"
#include "utils.hpp"
#include <cstdlib>
#include <regex>



Module SegmentDocker(const config& c) {

	Segment segment;

	segment.id      = segment::id::docker;
	segment.theme   = c.docker.theme;
	segment.content = utils::string(std::getenv("DOCKER_MACHINE_NAME"));

	if (segment)
	{
		return Module {segment};
	}

	segment.content = utils::string(std::getenv("DOCKER_HOST"));
	if (!segment)
	{
		return {};
	}

	// https://tools.ietf.org/html/rfc3986#appendix-B
	std::regex r (R"(^(([^:/?#]+):)?(//([^/?#]*))?([^?#]*)(\?([^#]*))?(#(.*))?)");
	segment.content = std::regex_replace(segment.content, r, "$4");

	if (segment)
	{
		return Module {segment};
	}
	return {};
}
