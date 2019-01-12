#include "theme.hpp"

#include <string>
#include <cstring>



Shell::Shell(const char* sh)
{
  char *s = strdup(sh);
  if (char *c = strchr(s, '-'))
  {
    s = c + 1;
  }
  if (char *c = strchr(s, '/'))
  {
    s = c + 1;
  }
  if (!strncmp(s, "zsh", 3))
  {
    escape_    = "%{\e[";
    epacse_    = "m%}";
    indicator_ = "%#";
    backslash_ = "\\";
    backtick_  = "\\`";
    dollar_    = "\\$";
  }
  else
  if (!strncmp(s, "fish", 4))
  {
    escape_    = "\x1b[",
    epacse_    = "\x1b(B\x1b[m";
    indicator_ = "$";
    backslash_ = "\\";
    backtick_  = "`";
    dollar_    = "$";
  }
  // else // Defaults to bash
  // {
  //   escape_    = "\e[";
  //   epacse_    = "m";
  //   indicator_ = "\\$";
  //   backslash_ = "\\\\";
  //   backtick_  = "\\`";
  //   dollar_    = "\\$";
  // };
  else // Defaults to bash
  {
    escape_    = "\\[\\e[";
    epacse_    = "m\\]";
    indicator_ = "\\$";
    backslash_ = "\\\\";
    backtick_  = "\\`";
    dollar_    = "\\$";
  };
}


Symbols::Symbols(std::shared_ptr<cpptoml::table> conf)
{
  auto symbols = conf->get_table("symbols");
  if (!symbols)
  {
    return;
  }

  cpptoml::option<std::string> i;
  if ((i = symbols -> get_as<std::string>("Lock")))          { Lock    = strdup(i->c_str());};
  if ((i = symbols -> get_as<std::string>("Network")))       { Network = strdup(i->c_str());};
  if ((i = symbols -> get_as<std::string>("Separator")))     { Separator = strdup(i->c_str());};
  if ((i = symbols -> get_as<std::string>("Separator")))     { Separator = strdup(i->c_str());};
  if ((i = symbols -> get_as<std::string>("SeparatorThin"))) { SeparatorThin = strdup(i->c_str());};
  if ((i = symbols -> get_as<std::string>("RSeparator")))    { RSeparator = strdup(i->c_str());};
  if ((i = symbols -> get_as<std::string>("RSeparatorThin"))){ RSeparatorThin = strdup(i->c_str());};
  if ((i = symbols -> get_as<std::string>("GitBranch")))     { GitBranch   = strdup(i->c_str());};
  if ((i = symbols -> get_as<std::string>("GitDetached")))   { GitDetached = strdup(i->c_str());};
  if ((i = symbols -> get_as<std::string>("GitAhead")))      { GitAhead  = strdup(i->c_str());};
  if ((i = symbols -> get_as<std::string>("GitBehind")))     { GitBehind = strdup(i->c_str());};
  if ((i = symbols -> get_as<std::string>("GitStaged")))     { GitStaged = strdup(i->c_str());};
  if ((i = symbols -> get_as<std::string>("GitNotStaged")))  { GitNotStaged  = strdup(i->c_str());};
  if ((i = symbols -> get_as<std::string>("GitConflicted"))) { GitConflicted = strdup(i->c_str());};
  if ((i = symbols -> get_as<std::string>("GitUntracked")))  { GitUntracked  = strdup(i->c_str());};
};


static inline void 
get_style_from_toml(Style& style, std::shared_ptr<cpptoml::table> k)
{
  if (cpptoml::option<int> i = k->get_as<int>("fg"))
  {
    style.fg = *i;
  }
  if (cpptoml::option<int> i = k->get_as<int>("bg"))
  {
    style.bg = *i;
  }
}

Theme::Theme(std::shared_ptr<cpptoml::table> conf)
{
  auto theme = conf->get_table("theme");
  if (!theme)
  {
    return;
  }

  int i;
  std::shared_ptr<cpptoml::table> k;
  if ((k = theme->get_table("Separator"))){get_style_from_toml(Separator, k);};
  if ((k = theme->get_table("Username"))){get_style_from_toml(Username, k);};
  if ((k = theme->get_table("UsernameRoot"))){get_style_from_toml(UsernameRoot, k);};
  if ((k = theme->get_table("Hostname"))){get_style_from_toml(Hostname, k);};
  if ((k = theme->get_table("Home"))){get_style_from_toml(Home, k);};
  if ((k = theme->get_table("Path"))){get_style_from_toml(Path, k);};
  if ((k = theme->get_table("Cwd"))){get_style_from_toml(Cwd, k);};
  if ((k = theme->get_table("Readonly"))){get_style_from_toml(Readonly, k);};
  if ((k = theme->get_table("Ssh"))){get_style_from_toml(Ssh, k);};
  if ((k = theme->get_table("DockerMachine"))){get_style_from_toml(DockerMachine, k);};
  if ((k = theme->get_table("KubeCluster"))){get_style_from_toml(KubeCluster, k);};
  if ((k = theme->get_table("KubeNamespace"))){get_style_from_toml(KubeNamespace, k);};
  if ((k = theme->get_table("DotEnv"))){get_style_from_toml(DotEnv, k);};
  if ((k = theme->get_table("Aws"))){get_style_from_toml(Aws, k);};
  if ((k = theme->get_table("RepoClean"))){get_style_from_toml(RepoClean, k);};
  if ((k = theme->get_table("RepoDirty"))){get_style_from_toml(RepoDirty, k);};
  if ((k = theme->get_table("Jobs"))){get_style_from_toml(Jobs, k);};
  if ((k = theme->get_table("CmdPassed"))){get_style_from_toml(CmdPassed, k);};
  if ((k = theme->get_table("CmdFailed"))){get_style_from_toml(CmdFailed, k);};
  if ((k = theme->get_table("SvnChanges"))){get_style_from_toml(SvnChanges, k);};
  if ((k = theme->get_table("GitAhead"))){get_style_from_toml(GitAhead, k);};
  if ((k = theme->get_table("GitBehind"))){get_style_from_toml(GitBehind, k);};
  if ((k = theme->get_table("GitStaged"))){get_style_from_toml(GitStaged, k);};
  if ((k = theme->get_table("GitNotStaged"))){get_style_from_toml(GitNotStaged, k);};
  if ((k = theme->get_table("GitUntracked"))){get_style_from_toml(GitUntracked, k);};
  if ((k = theme->get_table("GitConflicted"))){get_style_from_toml(GitConflicted, k);};
  if ((k = theme->get_table("GitStashed"))){get_style_from_toml(GitStashed, k);};
  if ((k = theme->get_table("VirtualEnv"))){get_style_from_toml(VirtualEnv, k);};
  if ((k = theme->get_table("VirtualGo"))){get_style_from_toml(VirtualGo, k);};
  if ((k = theme->get_table("Perlbrew"))){get_style_from_toml(Perlbrew, k);};
  if ((k = theme->get_table("TFWs"))){get_style_from_toml(TFWs, k);};
  if ((k = theme->get_table("Time"))){get_style_from_toml(Time, k);};
  if ((k = theme->get_table("ShellVar"))){get_style_from_toml(ShellVar, k);};
  if ((k = theme->get_table("Node"))){get_style_from_toml(Node, k);};
  if ((k = theme->get_table("Load"))){get_style_from_toml(Load, k);};
  if ((k = theme->get_table("NixShell"))){get_style_from_toml(NixShell, k);};
  if ((k = theme->get_table("Duration"))){get_style_from_toml(Duration, k);};
}
