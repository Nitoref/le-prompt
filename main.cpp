#include <ios>

#include "git3.hpp"



#include "prompt.hpp"
#include "promptOptions.hpp"


int main(int argc, char const *argv[])
{
    std::ios_base::sync_with_stdio(false);
    // PromptOpt opt = PromptOpt(&DefaultArgs, &Bash, &CurvySymbols, &LowContrast);
    PromptOpt opt = PromptOpt(&DefaultArgs, &Bash, &CurvySymbols, &SolarizedDark16);
    Prompt prompt = Prompt(opt);
    prompt.parseSegments("user,host,pwd,git2,root,exit");
    prompt.print();
}
