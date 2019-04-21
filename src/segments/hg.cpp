#include "modules.hpp"
#include <filesystem>
#include <iostream>
#include <string>


struct HgStatus
{
	std::string hash;
	std::string branch;
};


Module SegmentHg (const config& c)
{
	auto path = std::filesystem::current_path();
	auto hg = std::filesystem::path(".hg");
	bool found = false;

	for (;;)
	{
		if (std::filesystem::exists(path / hg))
		{
			found = true;
			break;
		}
		
		if (path == path.root_path()) {
			break;			
		}

		path = path.parent_path();
	}

	if (!found)
		return Module {};


	std::string branch = "default";

	std::ifstream i;
	i.open((path / hg / "branch").c_str());
	if (i.good())
	{
		i >> branch;
	}

	return Module {
		{
			module::id::hg,
			c.hg.symbol_branch + branch,
			c.hg.theme
		}
	};
}
