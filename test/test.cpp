#include "../lib/cpptoml.hpp"
#include "toml11/toml.hpp"
#include "nlohmann.hpp"

#include <algorithm>
#include <vector>
#include <iostream>
#include <iterator>
#include <functional>
#include <iostream>
#include <fstream>


int main(int argc, char **argv, char **envp)
{
  	const auto data  = toml::parse("/Users/nitoref/le_prompt/src/presets/alloptions.toml");
    const auto file = cpptoml::parse_file("/Users/nitoref/le_prompt/src/presets/alloptions.toml");
	std::cout << data;
}
