#include "prompt.hpp"
#include "parse_JSON.hpp"

#include <ios>
#include <string>
#include <iostream>
#include <fstream>

module::constructor_map_t module::constructor::map = {
    {"user",  SegmentUser},
    {"root",  SegmentShell},
    {"pwd",   SegmentPwd},
    {"exit",  SegmentExit},
    {"host",  SegmentHost},
    {"jobs",  SegmentJobs},
    {"git",   SegmentGit},
    {"time",  SegmentTime},
    {"perms", SegmentPerms},
    {"ssh",   SegmentSsh},
    {"aws",   SegmentAws},
    {"virtualenv", SegmentVirtualEnv}
};


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
            module::constructor::map.insert(e.begin(), e.end());
        }
    }
    catch (nlohmann::json::parse_error& e) {
        std::cout << "Config error: Wrong syntax\n"
                  << e.what();
    }
    catch (nlohmann::detail::type_error& e) {
        std::cout << "Config error: Wrong argument\n"
                  << e.what();
    }
    catch (std::system_error& e) {
        std::cout << "Error: Invalid config file\n"
                  << e.what();
    }
    catch (...) {
        std::cout << "Error: Invalid config file";
    }

    Prompt prompt { config };

    auto left_futures = module::constructor::spawn(config.args.left_segments, config);
    auto right_futures = module::constructor::spawn(config.args.right_segments, config);

    prompt.left_segments = module::constructor::join(left_futures, config.args.request_timeout);
    prompt.right_segments = module::constructor::join(right_futures, config.args.request_timeout);
	
    // prompt.left_segments = module::constructor::parse(config.args.left_segments, config);
    // prompt.right_segments = module::constructor::parse(config.args.right_segments, config);
	
	prompt.shrink();
    std::cout << prompt.print();
    exit(0);
}
