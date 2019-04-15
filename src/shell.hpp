#ifndef SHELL_H
#define SHELL_H

#include "utils.hpp"

#include <unistd.h>
#include <string>
#include <unordered_map>

struct Shell
{
    Shell() = default;

    enum Type {bash, dash, csh, ksh, zsh, fish, other};
    
    Type   id    = Type::other;
    bool   root  = false;
	int    error = 0;
    size_t width = 80;

    static Type type(std::string str)
    {
    	static std::unordered_map<std::string, Type>
    	shell_type_map {
	        {"sh",   Type::bash},
	        {"zsh",  Type::zsh},
	        {"ksh",  Type::ksh},
	        {"csh",  Type::csh},
	        {"tcsh", Type::csh},
	        {"bash", Type::bash},
	        {"dash", Type::dash},
	        {"fish", Type::fish},
    	};
    	auto item = shell_type_map.find(str);
		if (item != shell_type_map.end())
		{
			return item->second;
		}
		return Type::other;
    }

	Shell(std::string sh)
	{
		id    = Shell::type(sh);
        root  = getuid() == 0;
        width = utils::term_width();
	}
};

#endif
