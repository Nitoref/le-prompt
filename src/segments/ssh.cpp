#include <cstdlib>
#include "../modules.hpp"
#include "../utils.hpp"

Module SegmentSsh(const Config& c)
{
    return Module {
    	{
	    	module::id::ssh,
	    	utils::string(getenv("SSH_CLIENT")),
	    	c.theme.ssh
    	}
    };
}
