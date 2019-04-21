#include "../modules.hpp"


Module
SegmentRoot(const config& c)
{
	if (!c._meta.root)
	{
		return {};
	}

	return Module { {
		module::id::root,
		c.root.symbol,
		c.root.theme
	} };
}
