#ifndef SHELL_H
#define SHELL_H

#include "utils.hpp"

#include <unistd.h>
#include <string>
#include <map>


struct Shell
{
    enum Type {bash, csh, ksh, zsh, fish};

    Shell() = default;

	Shell(std::string sh)
	{
		id     = Shell::type(sh);
        root   = getuid() == 0;
        width  = utils::term_width();
        escape_map = get_escape_map(id);
	}


    Type   id    = Type::bash;
    bool   root  = false;
	int    error = 0;
    size_t width = 80;

    std::map<char, std::string> escape_map;


    static Type
    type(std::string str)
    {
    	static std::map<std::string, Type>
    	shell_type_map
    	{
	        {"bash", Type::bash},
	        {"csh",  Type::csh},
	        {"dash", Type::bash},
	        {"fish", Type::fish},
	        {"ksh",  Type::ksh},
	        {"sh",   Type::bash},
	        {"tcsh", Type::csh},
	        {"zsh",  Type::zsh},
    	};

    	auto item = shell_type_map.find(str);
		if (item != shell_type_map.end())
		{
			return item->second;
		}
		return Type::bash;
    }

    static std::map<char, std::string>
    get_escape_map(Type type)
    {
    	static std::map<Type, std::map<char, std::string>>
    	escape_characters_map
    	{
	        {Type::bash, {{'`', "\\`"}, {'$', "\\`"}} },
	        {Type::csh,  {{'%', "%%" }, {'!', "\\!"}} },
	        {Type::zsh,  {{'%', "%%" }} },
	        {Type::ksh,  {{'!', "!!" }} },
	        {Type::fish, {} },
    	};
		return escape_characters_map[type];
    }


};

#endif
