#include <pwd.h>
#include <unistd.h>
#include <string>
#include "../segments.hpp"
#include "../utils.hpp"



int
removeHome(std::string path)
{
    std::string home = utils::string::safe(std::getenv("HOME"));
    if (home.empty())
    {
        home = utils::string::safe(getpwuid(getuid())->pw_dir);
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

int
fold(std::string& path, int max_depth)
{
    std::string fold_symbol = "…";

    size_t stop = utils::string::rnfind(path, '/', max_depth);
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

Segment
SegmentPwd(PromptConfig p)
{
    Segment segment;
    segment.content = utils::string::safe(getenv("PWD"));
    removeHome(segment.content);

    for (auto& alias: p.args.path_aliases)
    {
        utils::string::replace_all(segment.content, alias.first, alias.second);
    };

    fold(segment.content, p.args.cwd_max_depth);
    segment.style = p.theme.path;

    return segment;
};
