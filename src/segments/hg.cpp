#include <filesystem>
#include <iostream>
#include <string>

#include "modules.hpp"



Segment SegmentHg (const config& c)
{
	auto path = std::filesystem::current_path();
	auto hg   = std::filesystem::path(".hg");
	bool found = false;

	while (true) {
		if (std::filesystem::exists(path / hg)) {
			found = true;
			break;
		}
		if (path == path.root_path()) {
			break;			
		}
		path = path.parent_path();
	}

	if (!found) {
		return {};
	}

	std::string branch;

	std::ifstream i((path / hg / "branch").c_str());
	if (i.good()) {
		i >> branch;
	} else {
		branch = "default";
	}

	Segment segment(segment::id::hg);
	segment.theme(c.hg.theme);
	segment.append(c.hg.symbol_branch);
	segment.append(branch);
	return segment;
}
