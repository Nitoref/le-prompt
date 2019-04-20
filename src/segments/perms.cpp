#include <unistd.h>
#include <filesystem>
#include "modules.hpp"


Module
SegmentPerms(const config& c)
{
    namespace fs = std::filesystem;
    auto path = fs::current_path();
    bool write_access = !access(path.c_str(), W_OK);

    std::string content;

    if (c.perms.verbose)
    {
        auto perms = fs::status(path).permissions();
        content += (perms & fs::perms::owner_read ) != fs::perms::none ? 'r' : '-';
        content += (perms & fs::perms::owner_write) != fs::perms::none ? 'w' : '-';
        content += (perms & fs::perms::owner_exec)  != fs::perms::none ? 'x' : '-';
        content += (perms & fs::perms::group_read)  != fs::perms::none ? 'r' : '-';
        content += (perms & fs::perms::group_write) != fs::perms::none ? 'w' : '-';
        content += (perms & fs::perms::group_exec)  != fs::perms::none ? 'x' : '-';
        content += (perms & fs::perms::others_read) != fs::perms::none ? 'r' : '-';
        content += (perms & fs::perms::others_write)!= fs::perms::none ? 'w' : '-';
        content += (perms & fs::perms::others_exec) != fs::perms::none ? 'x' : '-';
    }
    else
    if (!write_access)
    {
        content = c.perms.symbol_readonly;
    }

    return Module {
    	{
	    	module::id::perms,
	    	content,
	    	write_access ? c.perms.theme
                         : c.perms.theme_readonly
    	}
    };
}
