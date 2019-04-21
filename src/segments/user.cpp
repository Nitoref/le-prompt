#include <cstdlib>
#include "../modules.hpp"
#include "../utils.hpp"


Module
SegmentUser(const config& c)
{
    std::string content = utils::string(std::getenv("USER"));

    if(!c.user.always && content == c.user.default_user)
    {
    	return {};
    }

    return Module {
        {
            module::id::user,
            content,
            c._meta.root ? c.user.theme_root
                         : c.user.theme
        }
    };
}
