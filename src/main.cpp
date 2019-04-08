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

    if (prompt.options_.shell.name_ == "bash"
    ||  prompt.options_.shell.name_ == "tcsh"
    ||  prompt.options_.shell.name_ == "csh") {

    	int offset = prompt.options_.shell.width_ - prompt.right_length() + 2;
    	if (offset > prompt.left_length()) {
			prompt.printer_.wrap_mode(0);
    		output += prompt.printer_.wrap;
    		output += prompt.printer_.cup(offset);
    		output += prompt.format_right_segments();
    		output += prompt.printer_.cup(0);
    		output += prompt.printer_.unwrap;
    	}
		prompt.printer_.wrap_mode(1);
    	output += prompt.format_left_segments();
    	output += " ";
    }
    else {
    	output += prompt.format_left_segments();
    	output += '\n';
	    output += prompt.format_right_segments();
    }
    std::cout << output;
}
