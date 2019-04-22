#include "../modules.hpp"


Module
SegmentRoot(const config& c)
{
	if (!c._meta.root)
	{
		return {};
	}

	return Module { {
		segment::id::root,
		c.root.symbol,
		c.root.theme
	} };
}
