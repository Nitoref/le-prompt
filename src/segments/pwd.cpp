#include <pwd.h>
#include <unistd.h>
#include <string>
#include <string_view>
#include <iostream>
#include <filesystem>
#include "../modules.hpp"
#include "../utils.hpp"



void
remove_home(std::string& path)
{
    std::string home = utils::string::safe(std::getenv("HOME"));
    if (home.empty()) {
        home = utils::string::safe(getpwuid(getuid())->pw_dir);
    }
    if (home.empty()) {
        return;
    }
    if (path.find(home) != std::string::npos)
    {
        path.replace(0, home.length(), "~");
    }
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
SegmentPwd(Config c)
{
    std::string path = utils::string::safe(getenv("PWD"));
    remove_home(path);

    for (auto& [from, to]: c.args.path_aliases)
    {
        utils::string::replace_all(path, from, to);
    };

    fold(path, c.args.cwd_max_depth, c.symbols.cwd_wrap);

    if (c.args.cwd_mode == "simple")
    {
        return Module { {module::id::cwd, path, c.theme.path} };
    }

    Module module;
    for (auto dir: std::filesystem::path(path))
    {
        module.emplace_back(module::id::path, dir, c.theme.path);
    }
    module.back().style = c.theme.cwd;
    module.back().id = module::id::cwd;
    if (module.front().content[0] == '~')
    {
        module.front().id = module::id::home;
        module.front().style = c.theme.home;
    }

    return module;
}
