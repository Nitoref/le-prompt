#include <ios>
#include <string>
#include <iostream>

#include "utils.hpp"
#include "prompt.hpp"
#include "promptOptions.hpp"

#include "cpptoml.hpp"



int main(int argc, char const *argv[])
{
    std::ios_base::sync_with_stdio(false);
    std::shared_ptr<cpptoml::table> config;
    
    try
    {
        config  = cpptoml::parse_file(argv[4]);
    }
    catch(...)
    {
        std::cout << "Error parsing config.";
    }

    Arguments arg = config ? Arguments(config)
                           : Arguments();
    Symbols sym = config ? Symbols(config)
                         : Symbols();
    Theme  thm = config ? Theme(config)
                        : Theme();   

    PromptOpt opt = PromptOpt(arg, Bash, sym, thm);
    Prompt prompt = Prompt(opt);
    prompt.parseSegments();
    prompt.print();
}


// g++ -Oz -o build/powerline -std=c++17 *.cpp ./*/*.cpp -lgit2 -lyaml-cpp -I/usr/local/Cellar/yaml-cpp/0.6.2_1/include/yaml-cpp -Iinclude
