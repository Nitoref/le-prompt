#include <pwd.h>
#include <unistd.h>
#include <string.h>
#include "../modules.hpp"
#include "../utils.hpp"
#include "../string.hpp"



static
int
removeHome(string& path)
{
    string home {getenv("HOME")};
    if (home.empty())
    {
        home = string{getpwuid(getuid())->pw_dir};
    }
    if (home.empty())
    {
        return 0;
    }
    if (path.find(home) == std::string::npos)
    {   
        return 0;
    }
    path.replace(0, home.length(), "~");
    return 1;
}

static
int
fold(string& path)
{
    string fold_symbol = "…";

    size_t stop = path.rnfind('/', 3);
    if (stop == std::string::npos)
    {
        return 0;
    }
    size_t start = path.find('/');
    if (start == std::string::npos || start == stop)
    {
        return 0;
    }
    path.replace(start + 1, stop - start - 1, fold_symbol);
    return 1;
}

void
SegmentPwd::make()
{
    segment.content = string {getenv("PWD")};
    removeHome(segment.content);

    for (auto& alias: opt.args.path_aliases)
    {
        segment.content.replace_all(alias.first, alias.second);
    };

    fold(segment.content);
    segment.style = opt.theme.path;
};
