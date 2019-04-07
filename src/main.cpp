#include <ios>
#include "prompt.hpp"




int main(int argc, char const *argv[])
{
    std::ios_base::sync_with_stdio(false);
    Prompt prompt { PromptConfig { argv }};

    prompt.parse_segments();

    std::string output;
    output += prompt.print_left_segments();

    if (prompt.options_.shell.name_ == "bash")
    {
    	
    	std::string x = prompt.print_right_segments();
    	
    	int right_length = prompt.right_length();
    	int left_length  = prompt.left_length();
    	int offset = prompt.options_.shell.width_ - right_length - left_length + 2;

    	if (offset > 0) {
    		output += std::string(offset, ' ');
    		output += x;
    	}
    	
    	output.insert(0, "\\[");
    	output += "\\e[G";
    	output += "\\]";
    	output += "\\e[";
    	output += std::to_string(left_length + 2);
    	output += "C";
    }
    else
    {
    	output += '\n';
	    output += prompt.print_right_segments();
    }
    std::cout << output;
}
