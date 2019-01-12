#include <ios>
#include <string>
#include <iostream>

#include "utils.hpp"
#include "prompt.hpp"

#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    std::ios_base::sync_with_stdio(false);
    PromptOpt options;
    try {
        auto config = cpptoml::parse_file(argv[3]);
        options.args    = Arguments(config);
        options.symbols = Symbols(config);
        options.theme   = Theme(config);
    }
    catch(cpptoml::parse_exception& ex) {
        std::cerr << "Error parsing config file :\n\t" << ex.what() << std::endl;
    }

    // Get terminal width
    options.args.TermWidth = std::stoi(argv[4]);

    options.shell  = Shell(argv[1]);
    options.args.PrevError = std::stoi(argv[2]);

    Prompt prompt = Prompt(options);
    prompt.parseLeftSegments();
    prompt.printLeft();
}
