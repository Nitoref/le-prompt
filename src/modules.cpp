#include "modules.hpp"
#include "utils.hpp"
#include "parse_JSON.hpp"

#include <string>
#include <iostream>

void from_json(const nlohmann::json& j, module::constructor_map_t& m)
{
	Style style;
	std::string command;

	if (!j.is_object())
	{
		return;
	}

	for (auto& [name, segment]: j.items())
	{
		auto it = segment.find("command");
		if (it == segment.end())
		{
			continue;
		}

		command = it->get<std::string>();
		
		it = segment.find("style"); 
		if (it == segment.end())
		{
			continue;
		}

		style = it->get<Style>();

		m.emplace ( name, [=](Config c) -> Module {
			auto result = utils::exec(command);
			if (!result.empty())
			{
				return Module { {result[0], style} };
			}
			return Module {};
		});
	}
}
