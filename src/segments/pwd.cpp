#include <pwd.h>
#include <unistd.h>
#include <regex>
#include <string>
#include <string_view>
#include <iostream>
#include <filesystem>
#include "../modules.hpp"
#include "../utils.hpp"



int
remove_home(std::string& path, std::string symbol)
{
    std::string home = utils::string::safe(std::getenv("HOME"));
    if (home.empty()) {
        home = utils::string::safe(getpwuid(getuid())->pw_dir);
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
    size_t stop = utils::string::rnfind(path, '/', max_depth);
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
SegmentPwd(const Config& c)
{
    auto path = utils::string::safe(getenv("PWD"));
    bool at_home = remove_home(path, c.symbols.home);

    for (auto& [from, to]: c.args.path_aliases)
    {
        utils::string::replace_all(path, from, to);
    };

    fold(path, c.args.cwd_depth, c.symbols.cwd_wrap);

    for (auto& [what, with]: c.shell.escape_map) {
        utils::string::replace_all(path, what, with);
    }
    
    auto style = at_home ? c.theme.home : c.theme.path;
    return Module { {module::id::cwd, path, style } };


    // if (c.args.cwd_fancy == false)
    // {
    //     auto style = at_home ? c.theme.home : c.theme.path;
    //     return Module { {module::id::cwd, path, style } };
    // }

    // Module module;
    // for (auto dir: std::filesystem::path(path))
    // {
    //     module.emplace_back(module::id::path, dir, c.theme.path);
    // }
    // module.back().style = c.theme.cwd;
    // module.back().id = module::id::cwd;
    // if (at_home)
    // {
    //     module.front().id = module::id::home;
    //     module.front().style = c.theme.home;
    // }

    // return module;
}
