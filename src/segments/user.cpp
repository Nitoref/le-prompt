#include <cstdlib>
#include <unistd.h>
#include "../modules.hpp"
#include "../utils.hpp"


Module
SegmentUser(const config& c)
{
	Segment segment;
    segment.content = utils::string(getenv("USER"));

    if(segment.content == c.user.default_user
    && !c.user.always)
    {
    	return {Segment{}};
    }

    if (c._meta.root)
    {
        segment.style = c.user.theme_root;
    }
    else
    {
        segment.style = c.user.theme;
    }
    segment.id = module::id::user;
    return Module {segment};
}
