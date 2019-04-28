#include <map>
#include "modules.hpp"


Segment
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
		{shell_t::other , c.shell.symbol_all  },
	};

	Segment segment(segment::id::shell);

	if (!c.shell.symbol_all.empty()) {
		segment.append(c.shell.symbol_all);
	}
	else {
		segment.append(shell_symbols.at(c._meta.shell));
	}

	if (c._meta.error) {
		segment.theme(c.shell.theme_failure);
	}
	else {
		segment.theme(c.shell.theme_success);
	}

	return segment;
}
