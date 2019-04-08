#include "prompt.hpp"
#include <ios>
#include <string>
#include <iostream>



int main(int argc, char const *argv[])
{
    std::ios_base::sync_with_stdio(false);
    Prompt prompt { argc, argv };

    prompt.make_segments();
    std::string output;

    if (prompt.options.shell.name_ == "bash"
    ||  prompt.options.shell.name_ == "tcsh"
    ||  prompt.options.shell.name_ == "csh") {

    	int offset = prompt.options.shell.width_ - prompt.right_length() + 2;
    	if (offset > prompt.left_length()) {
			prompt.printer.wrap_mode(0);
    		output += prompt.printer.wrap;
    		output += prompt.printer.cup(offset);
    		output += prompt.format_right_segments();
    		output += prompt.printer.cup(0);
    		output += prompt.printer.unwrap;
    	}
		prompt.printer.wrap_mode(1);
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
