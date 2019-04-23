#include <map>
#include "modules.hpp"


Module
SegmentShell(const config& c)
{
	std::string symbol;
	std::map <shell_t, std::string> shell_symbols
	{
		{shell_t::bash  , c.shell.symbol_bash },
		{shell_t::csh   , c.shell.symbol_csh  },
		{shell_t::zsh   , c.shell.symbol_zsh  },
		{shell_t::ksh   , c.shell.symbol_ksh  },
		{shell_t::fish  , c.shell.symbol_fish },
		{shell_t::ps    , c.shell.symbol_ps   },
		{shell_t::other , c.shell.symbol_bash },
	};

    return Module {
        {
            segment::id::shell,
            shell_symbols.at(c._meta.shell),
            c._meta.error ? c.shell.theme_failure
                          : c.shell.theme_success

        }
    };
}
