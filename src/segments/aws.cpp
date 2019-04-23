#include "utils.hpp"
#include "modules.hpp"
#include <cstdlib>


Module SegmentAws(const config& c)
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

	auto content = c.aws.symbol;
	content += utils::string(content_cstr);

    return Module {
    	{
    		segment::id::aws,
			content,
			c.aws.theme
    	}
    };
}
