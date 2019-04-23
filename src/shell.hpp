#ifndef SHELL_H
#define SHELL_H

#include <map>



enum class shell_t
{ bash, csh, fish, ksh, zsh, ps, other };

inline shell_t
parse_shell (std::string name)
{
	const std::map<std::string, shell_t>
	map {
        {"bash", shell_t::bash},
        {"csh",  shell_t::csh},
        {"dash", shell_t::bash},
        {"fish", shell_t::fish},
        {"ksh",  shell_t::ksh},
        {"ps",   shell_t::ps},
        {"sh",   shell_t::bash},
        {"tcsh", shell_t::csh},
        {"zsh",  shell_t::zsh},
	};
	auto found = map.find(name);
	if (found != map.end())
		return found->second;
	return shell_t::other;
}



#endif
