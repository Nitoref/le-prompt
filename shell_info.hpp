#ifndef SHELL_H
#define SHELL_H

struct Shell
{
    Shell() = default;
    string escape_    = "\e[";
    string epacse_    = "m";
    string indicator_ = "$";
    string backslash_ = "\\";
    string backtick_  = "`";
    string dollar_    = "$";

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

		if (sh == "bash")
		{
			escape_    = "\\[\\e[";
			epacse_    = "m\\]";
			indicator_ = "\\$";
			backslash_ = "\\\\";
			backtick_  = "\\`";
			dollar_    = "\\$";
		}
		else
		if (sh == "zsh")
		{
			escape_    = "%{\e[";
			epacse_    = "m%}";
			indicator_ = "%#";
			backslash_ = "\\";
			backtick_  = "\\`";
			dollar_    = "\\$";
		};
	}
};

#endif
