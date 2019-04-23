#include "utils.hpp"
#include "modules.hpp"
#include <cstdlib>


Segment SegmentAws(const config& c)
{

	char* content_cstr = std::getenv("AWS_PROFILE");
	if (!content_cstr)
	{
		return {};
	}
	if (!c.aws.always && content_cstr == c.aws.ignore)
	{
		return {};
	}

	Segment segment(segment::id::aws);
	segment.theme(c.aws.theme);
	segment.append(c.aws.symbol);
	segment.append(utils::string(content_cstr));
	return segment;
}
