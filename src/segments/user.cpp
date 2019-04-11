#include <cstdlib>
#include <unistd.h>
#include "../modules.hpp"
#include "../utils.hpp"


Module
SegmentUser(Config c)
{
	Segment segment;
    segment.content = utils::string::safe(getenv("USER"));

    if(segment.content == c.args.default_user) {
    	return {Segment{}};
    }

    if (getuid() != 0) {
        segment.style = c.theme.username;
    }
    else {
        segment.style = c.theme.username_root;
    }
    segment.id = module::id::user;
    return Module {segment};
}
