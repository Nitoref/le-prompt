#include "../modules.hpp"


Module
SegmentShell(const config& c)
{
    return Module {
        {
            module::id::shell,
            c.prompt.symbol,
            c._meta.error ? c.prompt.theme_failure
                          : c.prompt.theme_success

        }
    };
}
