#include <pwd.h>
#include <unistd.h>
#include <regex>
#include <string>
#include <string_view>
#include <iostream>
#include <filesystem>

#include "modules.hpp"
#include "utils.hpp"



int
remove_home(std::string& path, std::string symbol)
{
    std::string home = utils::string(std::getenv("HOME"));
    if (home.empty()) {
        home = utils::string(getpwuid(getuid())->pw_dir);
    }
    if (home.empty()) {
        return 0;
    }
    if (path.find(home) != std::string::npos)
    {
        path.replace(0, home.length(), symbol);
        return 1;
    }
    return 0;
}

void
fold(std::string& path, int max_depth, std::string symbol)
{
    size_t stop = utils::strrnfind(path, '/', max_depth);
    if (stop == std::string::npos)
    {
        return;
    }

    size_t start = path.find('/');
    if (start == std::string::npos || start == stop)
    {
        return;
    }
    path.replace(start + 1, stop - start - 1, symbol);
    return;
}


Module
SegmentDir(const config& c)
{
    auto path = utils::string(getenv("PWD"));
    bool at_home = remove_home(path, c.dir.symbol_home);

    // for (auto& [from, to]: c.args.path_aliases)
    // {
    //     utils::strrepl(path, from, to);
    // };

    fold(path, c.dir.depth, c.dir.symbol_wrap);

    // for (auto& [what, with]: c.shell.escape_map) {
    //     utils::strrepl(path, what, with);
    // }
    
    auto style = at_home ? c.dir.theme_home : c.dir.theme_path;
    return Module { {module::id::dir, path, style } };


    // if (c.args.dir_fancy == false)
    // {
    //     auto style = at_home ? c.theme.home : c.theme.path;
    //     return Module { {module::id::dir, path, style } };
    // }

    // Module module;
    // for (auto dir: std::filesystem::path(path))
    // {
    //     module.emplace_back(module::id::path, dir, c.theme.path);
    // }
    // module.back().style = c.theme.dir;
    // module.back().id = module::id::dir;
    // if (at_home)
    // {
    //     module.front().id = module::id::home;
    //     module.front().style = c.theme.home;
    // }

    // return module;
}
