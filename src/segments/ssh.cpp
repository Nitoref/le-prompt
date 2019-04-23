#include <cstdlib>
#include "modules.hpp"
#include "utils.hpp"

Segment SegmentSsh(const config& c)
{
	char* content_cstr = std::getenv("SSH_CLIENT");
	if (!content_cstr)
	{
		content_cstr =  std::getenv("SSH_TTY");
	}

	if (!content_cstr)
	{
		return {};
	}

	Segment segment(segment::id::ssh);
	segment.theme(c.ssh.theme);
	segment.append(c.ssh.symbol);
	if (c.ssh.verbose)
	{
		segment.append(content_cstr);
	}
	return segment;
}
