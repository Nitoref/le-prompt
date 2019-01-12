#include <ios>
#include "prompt.hpp"

int main(int argc, char const *argv[])
{
    std::ios_base::sync_with_stdio(false);
    PromptOpt options(argv);
    Prompt prompt(options);
    prompt.parse_left_segments();
    prompt.print_left();
}
