#ifndef SHELL_H
#define SHELL_H

#include <string>


struct Shell
{
    Shell() = default;
    std::string escape_;
    std::string epacse_;
    std::string indicator_;
    std::string backslash_;
    std::string backtick_;
    std::string dollar_;

    std::string name_;
	int prev_error_;
    int width_;

	Shell(std::string sh)
	{
		if (size_t i = sh.find('-'); i != std::string::npos)
		{
			sh.erase(0, i+1);
		}
		if (size_t i = sh.rfind('/'); i != std::string::npos)
		{
			sh.erase(0, i+1);
		}
		name_ = sh;

		if (sh == "bash")
		{
			// escape_    = "\\e[";
			// epacse_    = "";
			// indicator_ = "$";
			escape_    = "\\[\\e[";
			epacse_    = "\\]";
			indicator_ = "\\$";
			backslash_ = "\\\\";
			backtick_  = "\\`";
			dollar_    = "\\$";
		}
		else
		if (sh == "zsh")
		{
			escape_    = "%{\e[";
			epacse_    = "%}";
			indicator_ = "%#";
			backslash_ = "\\";
			backtick_  = "\\`";
			dollar_    = "\\$";
		}
		else
		if (sh == "tcsh")
		{
			escape_    = "%{\\e[";
			epacse_    = "%}";
			indicator_ = "%#";
		}
		else
		{
		    escape_    = "\e[";
		    epacse_    = "";
		    indicator_ = "$";
		    backslash_ = "\\";
		    backtick_  = "`";
		    dollar_    = "$";
		};
	}
};

#endif
