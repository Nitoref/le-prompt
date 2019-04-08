#ifndef PROMPT_H
#define PROMPT_H

#include <iostream>
#include <fstream>

#include "parse_JSON.hpp"

#include "arguments.hpp"
#include "theme.hpp"
#include "symbols.hpp"
#include "shell_info.hpp"

#include "utils.hpp"



struct PromptConfig
{
    Arguments args;
    Symbols   symbols;
    Theme     theme;
    Shell     shell;

    PromptConfig(int argc, char const *argv[])
    {
        assert(argc >= 2 && "Thou shall provide $0 and $? as arguments. ($_ and $status for fish)");

        shell             =     Shell(argv[1]);
        shell.prev_error_ = std::stoi(argv[2]);
        shell.width_      = utils::term_width();

        if (argc < 4) {
            return;
        }

        try {
            std::ifstream i(argv[3]);
            nlohmann::json j;
            i >> j;
            if (auto k = j.find("args"); k != j.end()) {
                args = k->get<Arguments>();
            }
            if (auto k = j.find("theme"); k != j.end()) {
                theme = k->get<Theme>();
            }
            if (auto k = j.find("symbols"); k != j.end()) {
                symbols = k->get<Symbols>();
            }
        }
        catch (nlohmann::json::parse_error e) {
            std::cout << "Error parsing config file: Wrong syntax\n" << e.what();
        }
        catch (nlohmann::detail::type_error e) {
            std::cout << "Error parsing config file: Wrong argument\n" << e.what();
        }
        catch (std::system_error e) {
            std::cout << "Error: Invalid config file\n" << e.what();
        }
        catch (...) {
            std::cout << "Error: Unknown\n";
        }
    }
};

#endif
