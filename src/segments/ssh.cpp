#include <cstdlib>
#include "modules.hpp"
#include "utils.hpp"

Module SegmentSsh(const config& c)
{
	char* content_cstr = std::getenv("SSH_CLIENT");
	if (!content_cstr)
	{
		content_cstr =  std::getenv("SSH_TTY");
	}

	if (!content_cstr)
	{
		return Module {};
	}

	std::string content = c.ssh.symbol;
	if (c.ssh.verbose)
	{
		content += content_cstr;
	}

    return Module {
    	{
	    	segment::id::ssh,
	    	content,
	    	c.ssh.theme
    	}
    };
}
