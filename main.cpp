#include <ios>

#include "prompt.hpp"
#include "promptOptions.hpp"


int main(int argc, char const *argv[])
{
    std::ios_base::sync_with_stdio(false);
    PromptOpt opt = PromptOpt(DefaultArgs, Bash, CurvySymbols, LowContrast);
    Prompt prompt = Prompt(opt);
    prompt.parseSegments("user,host,pwd,git,root,exit");
    prompt.print();
}
