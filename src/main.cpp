// 858dba background

#include "prompt.hpp"
#include "parse_JSON.hpp"
#include "constructor.hpp"

#include <ios>
#include <string>
#include <iostream>
#include <fstream>

module::constructor_map_t module::constructor::map = {
    {"user",  SegmentUser},
    {"host",  SegmentHost},
    {"exit",  SegmentExit},
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
    {"venv", SegmentVirtualEnv}
};

// TODO 
// Escape '!' for ksh and csh




int main(int argc, char const *argv[])
{
    std::ios_base::sync_with_stdio(false);
    assert(argc >= 2 && "Thou shall provide shell name and $? ($status for fish) as arguments.\n");

    Config config;
    std::ifstream i;
    nlohmann::json j;
    config.shell        =     Shell(argv[1]);
    config.shell.error  = std::stoi(argv[2]);

    try
    {

    if (argc > 3)
    {
        i.open(argv[3]);
        i >> j;

        if (auto k = j.find("args"); k != j.end()) {
            config.args = k->get<Arguments>();
        }
        if (auto k = j.find("theme"); k != j.end()) {
            config.theme = k->get<Theme>();
        }
        if (auto k = j.find("symbols"); k != j.end()) {
            config.symbols = k->get<Symbols>();
        }
        if (auto k = j.find("extension"); k != j.end()) {
            auto e = k->get<module::constructor_map_t>();
            module::constructor::merge(e);
        }
    }

    }
    catch (nlohmann::json::parse_error& e) {
        std::cout << "<!config>";
    }
    catch (nlohmann::detail::type_error& e) {
        std::cout << "<!config>";
    }
    catch (std::system_error& e) {
        std::cout << "<!config>";
    }
    catch (...) {
        std::cout << "Invalid config file\n";
    }

    Prompt prompt { config };
    
    auto left_futures = module::constructor::spawn(config.args.left_segments, config);
    auto right_futures = module::constructor::spawn(config.args.right_segments, config);
    auto newline_futures = module::constructor::spawn(config.args.newline_segments, config);

    prompt.left_segments = module::constructor::join(left_futures, config.args.timeout);
    prompt.right_segments  = module::constructor::join(right_futures, config.args.timeout);
    prompt.newline_segments = module::constructor::join(newline_futures, config.args.timeout);

    std::cout << prompt.print();
}
