#include <stdlib.h>
#include "../modules.hpp"


Module
SegmentShell(Config c)
{
	Segment segment;

    switch (c.shell.id)
    {
    case Shell::bash:
        segment.content = c.symbols.bash;
        break;

    case Shell::zsh:
        segment.content = c.symbols.zsh;
        break;

    case Shell::fish:
        segment.content = c.symbols.fish;
        break;

    case Shell::tcsh:
        segment.content = c.symbols.tcsh;
        break;

    case Shell::csh:
        segment.content = c.symbols.csh;
        break;

    default:
        segment.content = c.symbols.bash;
        break;
    }

    if (!c.shell.error)
    {
        segment.style = c.theme.cmd_passed;
    }
    else
    {
        segment.style = c.theme.cmd_failed;
    }

    segment.id = module::id::shell;
    return Module {segment};
}
