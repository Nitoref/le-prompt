#include <filesystem>
#include "modules.hpp"

#ifdef _WIN32
#   include <windows.h>
#else
#   include <unistd.h>
#endif


Module
SegmentPerms(const config& c)
{
    namespace fs = std::filesystem;
    auto path = fs::current_path();

#ifdef _WIN32
    bool write_access = !_access(path.c_str(), W_OK);
#else
    bool write_access = !access(path.c_str(), W_OK);
#endif
    
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
	    	segment::id::perms,
	    	content,
	    	write_access ? c.perms.theme
                         : c.perms.theme_readonly
    	}
    };
}
