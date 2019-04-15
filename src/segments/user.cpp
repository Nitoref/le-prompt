#include <cstdlib>
#include <unistd.h>
#include "../modules.hpp"
#include "../utils.hpp"


Module
SegmentUser(const Config& c)
{
	Segment segment;
    segment.content = utils::string(getenv("USER"));

    if(segment.content == c.args.default_user)
    {
    	return {Segment{}};
    }

    if (c.shell.root)
    {
        segment.style = c.theme.root;
    }
    else
    {
        segment.style = c.theme.username;
    }
    segment.id = module::id::user;
    return Module {segment};
}
