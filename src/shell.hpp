#ifndef SHELL_H
#define SHELL_H

#include "utils.hpp"

#include <string>
#include <unordered_map>

struct Shell
{
    enum Type {bash, csh, tcsh, zsh, fish, other};
    
    Shell() = default;
    std::string wrap;
    std::string unwrap;
    std::string escape;
    std::string indicator;
    std::string backslash;
    std::string backtick;
    std::string dollar;

    Type id   = Type::other;
	int error = 0;
    int width = 80;

    static Type type(std::string str)
    {
    	static std::unordered_map<std::string, Type>
    	shell_type_map {
	        {"csh",  Type::csh},
	        {"tcsh", Type::tcsh},
	        {"sh",   Type::bash},
	        {"bash", Type::bash},
	        {"fish", Type::fish},
	        {"zsh",  Type::zsh},
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
		id = Shell::type(sh);
        width = utils::term_width();
	}
};

#endif
