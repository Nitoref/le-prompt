#include "../modules.hpp"


Module
SegmentRoot(const config& c)
{
	if (!c._meta.root)
	{
		return Module {};
	}

	return Module { {
		module::id::root,
		c.root.symbol,
		c.root.theme
	} };
}
