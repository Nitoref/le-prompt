#include "../modules.hpp"


Module
SegmentRoot(const Config& c)
{
	if (!c.shell.root)
	{
		return Module {};
	}

	return Module { {
		module::id::root,
		c.symbols.root,
		c.theme.root
	} };
}
