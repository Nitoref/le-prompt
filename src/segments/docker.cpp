#include "modules.hpp"
#include "utils.hpp"
#include <cstdlib>
#include <regex>



Segment
SegmentDocker(const config& c)
{

	Segment segment(segment::id::docker);
	segment.theme(c.docker.theme);

	char* content_cstr = std::getenv("DOCKER_MACHINE_NAME");
	if (content_cstr)
	{
		segment += content_cstr;
		return segment;
	}

	content_cstr = std::getenv("DOCKER_HOST");
	if (!content_cstr)
	{
		return {};
	}

	// https://tools.ietf.org/html/rfc3986#appendix-B
	std::regex r (R"(^(([^:/?#]+):)?(//([^/?#]*))?([^?#]*)(\?([^#]*))?(#(.*))?)");
	auto content = utils::string(content_cstr);
	segment.append(std::regex_replace(content, r, "$4"));
	return segment;
}
