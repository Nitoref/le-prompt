// 858dba background

#include "prompt.hpp"
#include "toml_parse.hpp"
#include "constructor.hpp"

#include <ios>
#include <string>
#include <iostream>

constructor_map_t constructor::map = {
    {"user",   SegmentUser},
    {"context",SegmentContext},
    {"status", SegmentStatus},
    {"root",   SegmentRoot},
    {"shell",  SegmentShell},
    {"jobs",   SegmentJobs},
    {"time",   SegmentTime},
    {"dir",    SegmentDir},
    {"git",    SegmentGit},
    {"perms",  SegmentPerms},
    {"ssh",    SegmentSsh},
    {"aws",    SegmentAws},
    {"docker", SegmentDocker},
    {"venv",   SegmentVirtualEnv}
};


int main(int argc, char const *argv[])
{
    std::ios_base::sync_with_stdio(false);

    config conf {argc, argv};
    
    Printer::mode(conf._meta.shell);
    
    Prompt prompt { conf };
    
    auto left_futures  = constructor::spawn(conf.segments.left, conf);
    auto right_futures = constructor::spawn(conf.segments.right, conf);
    auto down_futures  = constructor::spawn(conf.segments.down, conf);

    prompt.left.segments  = constructor::join(left_futures, conf.global.timeout);
    prompt.right.segments = constructor::join(right_futures, conf.global.timeout);
    prompt.down.segments  = constructor::join(down_futures, conf.global.timeout);

    std::cout << prompt.make();
}
