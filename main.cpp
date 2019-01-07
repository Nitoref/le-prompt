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
    
    Arguments a;
    Symbols s;
    Theme t = Theme();

    try{
        config  = cpptoml::parse_file(argv[4]);
    }
    catch(...){
        std::cout << "Error parsing config";
        return 1;
    }

    auto args = config->get_table("args");
    a = args ? Arguments(args) : Arguments();
    auto symbols = config->get_table("symbols");
    s = symbols ? Symbols(symbols) : Symbols();
    auto theme = config->get_table("theme");
    t = theme ? Theme(theme) : Theme();


    PromptOpt opt = PromptOpt(a, Bash, s, t);
    Prompt prompt = Prompt(opt);
    prompt.parseSegments("user,host,pwd,git,root,exit");
    prompt.print();
}


// g++ -Oz -o build/powerline -std=c++17 *.cpp ./*/*.cpp -lgit2 -lyaml-cpp -I/usr/local/Cellar/yaml-cpp/0.6.2_1/include/yaml-cpp -Iinclude
