#include <cstdlib>
#include "modules.hpp"
#include "utils.hpp"

Module SegmentSsh(const config& c)
{
    return Module {
    	{
	    	module::id::ssh,
	    	utils::string(std::getenv("SSH_CLIENT")),
	    	c.ssh.theme
    	}
    };
}
