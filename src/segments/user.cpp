#include <cstdlib>
#include <unistd.h>
#include "../segments.hpp"
#include "../utils.hpp"


Segment
SegmentUser(PromptConfig p)
{
	Segment segment;
    segment.content = utils::string::safe(getenv("USER"));

    if(segment.content == p.args.default_user) {
    	return Segment{};
    }

    if (getuid() != 0) {
        segment.style = p.theme.username;
    }
    else {
        segment.style = p.theme.username_root;
    }

    return segment;
};
