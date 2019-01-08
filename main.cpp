#include <ios>
#include <string>
#include <iostream>

#include "utils.hpp"
#include "prompt.hpp"
#include "promptOptions.hpp"

#include "cpptoml.hpp"



int main(int argc, char const *argv[])
{
    Arguments arg;
    Symbols sym;
    Theme  thm;
    Shell sh;

    std::ios_base::sync_with_stdio(false);
    std::shared_ptr<cpptoml::table> config;
    
    try {
        config  = cpptoml::parse_file(argv[3]);}
    catch(...) {
        std::cout << "Error parsing config file.";}

    arg = config ? Arguments(config)
                 : Arguments();
    sym = config ? Symbols(config)
                 : Symbols();
    thm = config ? Theme(config)
                 : Theme();
    sh  = Shell(argv[1]);

    arg.PrevError = std::stoi(argv[2]);
    
    PromptOpt opt = PromptOpt(arg, sh, sym, thm);

    Prompt prompt = Prompt(opt);
    prompt.parseSegments();
    prompt.print();
}


// g++ -Oz -o build/powerline -std=c++17 *.cpp ./*/*.cpp -lgit2 -Iinclude
