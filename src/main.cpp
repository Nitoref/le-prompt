#include <ios>
#include "prompt.hpp"

#include <string>
#include <iostream>



int main(int argc, char const *argv[])
{
    std::ios_base::sync_with_stdio(false);
    Prompt prompt { PromptConfig { argc, argv }};

    prompt.make_segments();
    std::string output;


    if (prompt.options_.shell.name_ == "bash" || prompt.options_.shell.name_ == "tcsh")
    {
    	int right_length = prompt.right_length();
    	int left_length  = prompt.left_length();
    	int offset = prompt.options_.shell.width_ - right_length;

    	if (offset > 0) {
    		// output += "\\[";
    		output += std::string(offset, ' ');
    		output += prompt.format_right_segments();
    		// output += "\\e[G";
    		// output += "\\]";
    	}
    	output += prompt.options_.shell.escape_ + 'G' + prompt.options_.shell.escape_;
    	output += prompt.format_left_segments();
    }
    else
    {
    	output += prompt.format_left_segments();
    	output += '\n';
	    output += prompt.format_right_segments();
    }
    std::cout << output;
}
