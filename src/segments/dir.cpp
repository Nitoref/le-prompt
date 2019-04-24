#ifdef _WIN32
#   include <windows.h>
#else
#   include <pwd.h>
#   include <unistd.h>
#endif
#include <regex>
#include <string>
#include <filesystem>

#include "modules.hpp"
#include "utils.hpp"


int
truncate_home(std::string& path, std::string symbol)
{

#ifdef _WIN32
    std::string home = utils::string(std::getenv("USERPROFILE"));
    if (home.empty()) {
        home =  std::getenv("HOMEDRIVE");
        home += std::getenv("HOMEPATH");
    }
#else
    std::string home = utils::string(std::getenv("HOME"));
    if (home.empty()) {
        home = utils::string(getpwuid(getuid())->pw_dir);
    }
#endif
    if (home.empty()) {
        return 0;
    }
    if (path.find(home) != std::string::npos)
    {
        path = "~" + path.substr(home.length());
        return 1;
    }
    return 0;
}


void
truncate_depth(std::string& path_str, int max_depth, std::string symbol)
{
    auto path = std::filesystem::path(path_str);
    size_t path_depth = std::distance(path.begin(), path.end());
    if (path_depth - 1 > max_depth)
    {
        auto path_iterator = path.begin();
        auto truncated = *path_iterator / symbol;
        for (int i = 0; i < path_depth - max_depth; ++i) 
        {
            ++path_iterator;
        }

        for (; path_iterator != path.end(); ++path_iterator)
        {
            truncated /= *path_iterator;
        }
        path = truncated.string();
    }
}


Segment
SegmentDir(const config& c)
{

    std::string path    = c._meta.cwd.string();
    bool at_home = truncate_home(path, c.dir.symbol_home);

    if (!c.dir.alias.empty())
    {
        for (auto& [what, with]: c.dir.alias)
        {
            utils::strrepl(path, what, with);
        };
    }

    if (c.dir.depth > 0)
    {
        truncate_depth(path, c.dir.depth, c.dir.symbol_wrap);
    }

    Segment segment(segment::id::dir);
    segment.append(path);
    if (at_home)
        segment.theme(c.dir.theme_home);
    else
        segment.theme(c.dir.theme_path);
    return segment;
}
