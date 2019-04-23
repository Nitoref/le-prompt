#include "../modules.hpp"


Segment
SegmentRoot(const config& c)
{
	if (!c._meta.root)
	{
		return {};
	}

	Segment segment(segment::id::root);
	segment.append(c.root.symbol);
	segment.theme(c.root.theme);
	return segment;
}
