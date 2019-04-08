#ifndef SHELL_H
#define SHELL_H

#include <string>


struct Shell
{
    Shell() = default;
    std::string wrap;
    std::string unwrap;
    std::string escape;
    std::string indicator;
    std::string backslash;
    std::string backtick;
    std::string dollar;

    enum {bash, tcsh, zsh, other};

    std::string name_;
	int prev_error_;
    int width_;

	Shell(std::string sh)
	{
		if (size_t i = sh.find('-'); i != std::string::npos) {
			sh.erase(0, i+1);
		}
		if (size_t i = sh.rfind('/'); i != std::string::npos) {
			sh.erase(0, i+1);
		}
		name_ = sh;

		if (sh == "bash") {
			wrap       = "\\[";
			unwrap     = "\\]";
			escape     = "\u001b[";

			indicator  = "\\$";
			backslash  = "\\\\";
			backtick   = "\\`";
			dollar     = "\\$";
		}
		else
		if (sh == "zsh") {
			wrap       = "%{";
			unwrap     = "%}";
			escape     = "\u001b[";
			
			indicator  = "%#";
			backslash  = "\\";
			backtick   = "\\`";
			dollar     = "\\$";
		}
		else
		if (sh == "tcsh" || sh == "csh") {
			wrap       = "%{";
			unwrap     = "%}";
			escape     = "\u001b[";
			indicator  = "%#";
		}
		else {
		    wrap       = "";
		    unwrap     = "";
		    escape     = "\u001b[";

		    indicator  = "$";
		    backslash  = "\\";
		    backtick   = "`";
		    dollar     = "$";
		};
	}
};

#endif
