#include <string>
#include "../utils.hpp"
#include "../segments.hpp"

const char *git_status_cmd =
"git status "
"-b "
"--porcelain "
"--ignore-submodules "
"2> /dev/null";

const char *git_toplevel_cmd =
"git rev-parse "
"--show-toplevel "
"2> /dev/null";

const char *git_detached_head_cmd =
"git rev-parse "
"--short HEAD "
"2> /dev/null";


Segment*
segmentGit(PromptOpt *p)
{
    std::string out = exec("git rev-parse --short HEAD");
    // std::string out = exec(git_status_cmd);
    // char *out = getCommandOutput(git_status_cmd);
    return NULL;
}
