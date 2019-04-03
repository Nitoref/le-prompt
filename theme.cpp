#include "theme.hpp"


Shell::Shell(std::string sh)
{
  if (size_t i = sh.find('-'); i != std::string::npos)
    sh.erase(0, i+1);
  if (size_t i = sh.rfind('/'); i != std::string::npos)
    sh.erase(0, i+1);

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
