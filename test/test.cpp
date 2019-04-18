#include <algorithm>
#include <vector>
#include <iostream>
#include <iterator>
#include <functional>
#include <iostream>

int main(int argc, char **argv, char **envp)
{
	std::string s = "hello%you%two";
	std::string o;
	std::transform(
		s.begin(), s.end(),
		std::back_inserter(o),
        [](char c) -> std::string { if (c == '%') return "%%"; return std::string(1, c); }
    );

}
