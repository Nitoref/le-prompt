#include <pwd.h>
#include <unistd.h>
#include <string>
#include "../segments.hpp"
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
    if (path.find(home) == std::string::npos) {   
        return;
    }
    path.replace(0, home.length(), "~");
    return;
}

void
fold(std::string& path, int max_depth, std::string symbol)
{
    size_t stop = utils::string::rnfind(path, '/', max_depth);
    if (stop == std::string::npos) {
        return;
    }

    size_t start = path.find('/');
    if (start == std::string::npos || start == stop) {
        return;
    }
    path.replace(start + 1, stop - start - 1, symbol);
    return;
}

MultiSegment
SegmentPwd(PromptConfig p)
{
    Segment segment;
    segment.content = utils::string::safe(getenv("PWD"));
    remove_home(segment.content);

    // for (auto& alias: p.args.path_aliases) {
    //     utils::string::replace_all(segment.content, alias.first, alias.second);
    // };

    // fold(segment.content, p.args.cwd_max_depth, p.symbols.cwd_wrap);
    segment.style = p.theme.path;

    return {segment};
};
