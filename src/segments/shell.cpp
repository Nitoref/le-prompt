#include "../modules.hpp"


Module
SegmentShell(const Config& c)
{
    return Module {
        {
            module::id::shell,
            c.symbols.prompt,
            c.shell.error ? c.theme.exit_failure
                          : c.theme.exit_success

        }
    };
}
