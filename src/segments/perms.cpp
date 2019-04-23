#include <filesystem>
#include "modules.hpp"

#ifdef _WIN32
#   include <windows.h>
#else
#   include <unistd.h>
#endif


Segment
SegmentPerms(const config& c)
{
    namespace fs = std::filesystem;
    auto path = c._meta.cwd;

#ifdef _WIN32
    bool write_access = !_access(path.c_str(), W_OK);
#else
    bool write_access = !access(path.c_str(), W_OK);
#endif
    
    Segment segment(segment::id::perms);

    if (c.perms.verbose)
    {
        if (!write_access)
            segment.theme(c.perms.theme_readonly);
        else
            segment.theme(c.perms.theme);
     
        std::string content;
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
        segment.append(content);
    }
    else
    if (!write_access)
    {
        segment.theme(c.perms.theme_readonly);
        segment.append(c.perms.symbol_readonly);
    }

    return segment;
}
