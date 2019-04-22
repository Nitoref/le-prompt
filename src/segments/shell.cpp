#include <map>
#include "modules.hpp"


Module
SegmentShell(const config& c)
{
	std::string symbol;
	std::map <config::shell_t, std::string> shell_symbols
	{
		{config::bash  , c.prompt.symbol_bash },
		{config::csh   , c.prompt.symbol_csh  },
		{config::zsh   , c.prompt.symbol_zsh  },
		{config::ksh   , c.prompt.symbol_ksh  },
		{config::fish  , c.prompt.symbol_fish },
		{config::ps    , c.prompt.symbol_ps   },
		{config::other , c.prompt.symbol_bash },
	};

    return Module {
        {
            segment::id::shell,
            shell_symbols.at(c._meta.shell),
            c._meta.error ? c.prompt.theme_failure
                          : c.prompt.theme_success

        }
    };
}
