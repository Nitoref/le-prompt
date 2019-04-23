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
truncate_home(std::filesystem::path& path, std::string symbol)
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
    if (path.string().find(home) != std::string::npos)
    {
        std::filesystem::path output ("~" + path.string().substr(home.length()));
        path.swap(output);
        return 1;
    }
    return 0;
}


void
truncate_depth(std::filesystem::path& path, int max_depth, std::string symbol)
{
    size_t path_depth = std::distance(path.begin(), path.end());
    if (path_depth - 1 > max_depth)
    {
        auto path_iterator = path.begin();
        auto output = *path_iterator / symbol;
        for (int i = 0; i < path_depth - max_depth; i++) 
        {
            path_iterator++;
        }

        for (; path_iterator != path.end(); ++path_iterator)
        {
            output /= *path_iterator;
        }
        path.swap(output);
    }
}


Segment
SegmentDir(const config& c)
{

    auto path    = c._meta.cwd;
    bool at_home = truncate_home(path, c.dir.symbol_home);

    if (!c.dir.alias.empty())
    {
        std::string output = path.string();
        for (auto& [what, with]: c.dir.alias)
        {
            utils::strrepl(output, what, with);
        };
        path = output;
    }

    if (c.dir.depth > 0)
    {
        truncate_depth(path, c.dir.depth, c.dir.symbol_wrap);
    }

    Segment segment(segment::id::dir);
    segment.append(path.string());
    if (at_home)
        segment.theme(c.dir.theme_home);
    else
        segment.theme(c.dir.theme_path);
    return segment;
}
