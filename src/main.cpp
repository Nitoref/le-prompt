// 858dba background

#include "prompt.hpp"
#include "toml_parse.hpp"
#include "constructor.hpp"

#include <ios>
#include <string>
#include <iostream>

module::constructor_map_t module::constructor::map = {
    {"user",  SegmentUser},
    {"host",  SegmentHost},
    {"status",SegmentStatus},
    {"root",  SegmentRoot},
    {"shell", SegmentShell},
    {"jobs",  SegmentJobs},
    {"time",  SegmentTime},
    {"dir",   SegmentDir},
    {"git",   SegmentGit},
    {"perms", SegmentPerms},
    {"ssh",   SegmentSsh},
    {"aws",   SegmentAws},
    {"docker",SegmentDocker},
    {"venv",  SegmentVirtualEnv}
};


int main(int argc, char const *argv[])
{
    std::ios_base::sync_with_stdio(false);
    assert(argc >= 2 && "Thou shall provide shell name and $? ($status for fish) as arguments.\n");


    Config config;
    config.shell        =     Shell(argv[1]);
    config.shell.error  = std::stoi(argv[2]);

    if (argc > 3)
    try
    {
        toml::parse(config, argv[3]);
    }
    catch (...) {
        std::cout << "<!config>";
    }

    Prompt prompt { config };
    Printer::mode(config.shell.id);
    
    auto left_futures  = module::constructor::spawn(config.args.left_segments, config);
    auto right_futures = module::constructor::spawn(config.args.right_segments, config);
    auto down_futures  = module::constructor::spawn(config.args.down_segments, config);

    prompt.left.segments  = module::constructor::join(left_futures, config.args.timeout);
    prompt.right.segments = module::constructor::join(right_futures, config.args.timeout);
    prompt.down.segments  = module::constructor::join(down_futures, config.args.timeout);

    std::cout << prompt.make();
}
