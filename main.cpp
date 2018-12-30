#include <iostream>
#include <cstring>
#include <vector>
#include <array>

#include "prompt.hpp"
#include "promptOptions.hpp"


int main(int argc, char const *argv[])
{
    const char *modules = "user,host,pwd";
    PromptOpt opt = PromptOpt(&DefaultArgs, &Bash, &CurvySymbols, &LowContrast);
    Prompt prompt = Prompt(opt);
    prompt.appendSegment("user");
    prompt.appendSegment("host");
    prompt.appendSegment("pwd");
    prompt.appendSegment("root");
    prompt.appendSegment("exit");
    prompt.print();
}
