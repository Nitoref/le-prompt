#include "theme.hpp"
#include <memory>
#include <cstring>


const ShellInfo Bash =
{
     .colorTemplate = "\\[\\e%s\\]",
     .rootIndicator = "\\$",
  .escapedBackslash = "\\\\",
   .escapedBacktick = "\\`",
     .escapedDollar = "\\$",
};

const ShellInfo Zsh =
{
     .colorTemplate = "%%{\e%s%%}",
     // .colorTemplate = "%%{\u001b%s%%}",
     .rootIndicator = "%#",
  .escapedBackslash = "\\",
   .escapedBacktick = "\\`",
     .escapedDollar = "\\$",
};

const ShellInfo Bare =
{
     // .colorTemplate = "%s",
     .colorTemplate = "\e%s",
     .rootIndicator = "$",
  .escapedBackslash = "\\",
   .escapedBacktick = "`",
     .escapedDollar = "$",
};


Symbols::Symbols(std::shared_ptr<cpptoml::table> conf)
{
  auto symbols = conf->get_table("symbols");
  if (!symbols)
    return;

  cpptoml::option<std::string> i;
  if ((i = conf->get_as<std::string>("Lock"))){Lock = strdup(i->c_str());};
  if ((i = conf->get_as<std::string>("Network"))){Network = strdup(i->c_str());};
  if ((i = conf->get_as<std::string>("Separator"))){Separator = strdup(i->c_str());};
  if ((i = conf->get_as<std::string>("SeparatorThin"))){SeparatorThin = strdup(i->c_str());};
  if ((i = conf->get_as<std::string>("GitBranch"))){GitBranch = strdup(i->c_str());};
  if ((i = conf->get_as<std::string>("GitDetached"))){GitDetached = strdup(i->c_str());};
  if ((i = conf->get_as<std::string>("GitAhead"))){GitAhead = strdup(i->c_str());};
  if ((i = conf->get_as<std::string>("GitBehind"))){GitBehind = strdup(i->c_str());};
  if ((i = conf->get_as<std::string>("GitStaged"))){GitStaged = strdup(i->c_str());};
  if ((i = conf->get_as<std::string>("GitNotStaged"))){GitNotStaged = strdup(i->c_str());};
  if ((i = conf->get_as<std::string>("GitConflicted"))){GitConflicted = strdup(i->c_str());};
  if ((i = conf->get_as<std::string>("GitUntracked"))){GitUntracked = strdup(i->c_str());};
};


inline void getStyleFromToml(Style& style, std::shared_ptr<cpptoml::table> k)
{
  if (cpptoml::option<int> i = k->get_as<int>("fg"))
    style.fg = *i;
  if (cpptoml::option<int> i = k->get_as<int>("bg"))
    style.bg = *i;
}

Theme::Theme(std::shared_ptr<cpptoml::table> conf)
{
  // std::shared_ptr<cpptoml::table> theme = conf->get_table("theme");
  auto theme = conf->get_table("theme");
  if (!theme)
    return;

  int i;
  std::shared_ptr<cpptoml::table> k;
  if ((k = theme->get_table("Separator"))){getStyleFromToml(Separator, k);};
  if ((k = theme->get_table("Username"))){getStyleFromToml(Username, k);};
  if ((k = theme->get_table("UsernameRoot"))){getStyleFromToml(UsernameRoot, k);};
  if ((k = theme->get_table("Hostname"))){getStyleFromToml(Hostname, k);};
  if ((k = theme->get_table("Home"))){getStyleFromToml(Home, k);};
  if ((k = theme->get_table("Path"))){getStyleFromToml(Path, k);};
  if ((k = theme->get_table("Cwd"))){getStyleFromToml(Cwd, k);};
  if ((k = theme->get_table("Readonly"))){getStyleFromToml(Readonly, k);};
  if ((k = theme->get_table("Ssh"))){getStyleFromToml(Ssh, k);};
  if ((k = theme->get_table("DockerMachine"))){getStyleFromToml(DockerMachine, k);};
  if ((k = theme->get_table("KubeCluster"))){getStyleFromToml(KubeCluster, k);};
  if ((k = theme->get_table("KubeNamespace"))){getStyleFromToml(KubeNamespace, k);};
  if ((k = theme->get_table("DotEnv"))){getStyleFromToml(DotEnv, k);};
  if ((k = theme->get_table("Aws"))){getStyleFromToml(Aws, k);};
  if ((k = theme->get_table("RepoClean"))){getStyleFromToml(RepoClean, k);};
  if ((k = theme->get_table("RepoDirty"))){getStyleFromToml(RepoDirty, k);};
  if ((k = theme->get_table("Jobs"))){getStyleFromToml(Jobs, k);};
  if ((k = theme->get_table("CmdPassed"))){getStyleFromToml(CmdPassed, k);};
  if ((k = theme->get_table("CmdFailed"))){getStyleFromToml(CmdFailed, k);};
  if ((k = theme->get_table("SvnChanges"))){getStyleFromToml(SvnChanges, k);};
  if ((k = theme->get_table("GitAhead"))){getStyleFromToml(GitAhead, k);};
  if ((k = theme->get_table("GitBehind"))){getStyleFromToml(GitBehind, k);};
  if ((k = theme->get_table("GitStaged"))){getStyleFromToml(GitStaged, k);};
  if ((k = theme->get_table("GitNotStaged"))){getStyleFromToml(GitNotStaged, k);};
  if ((k = theme->get_table("GitUntracked"))){getStyleFromToml(GitUntracked, k);};
  if ((k = theme->get_table("GitConflicted"))){getStyleFromToml(GitConflicted, k);};
  if ((k = theme->get_table("GitStashed"))){getStyleFromToml(GitStashed, k);};
  if ((k = theme->get_table("VirtualEnv"))){getStyleFromToml(VirtualEnv, k);};
  if ((k = theme->get_table("VirtualGo"))){getStyleFromToml(VirtualGo, k);};
  if ((k = theme->get_table("Perlbrew"))){getStyleFromToml(Perlbrew, k);};
  if ((k = theme->get_table("TFWs"))){getStyleFromToml(TFWs, k);};
  if ((k = theme->get_table("Time"))){getStyleFromToml(Time, k);};
  if ((k = theme->get_table("ShellVar"))){getStyleFromToml(ShellVar, k);};
  if ((k = theme->get_table("Node"))){getStyleFromToml(Node, k);};
  if ((k = theme->get_table("Load"))){getStyleFromToml(Load, k);};
  if ((k = theme->get_table("NixShell"))){getStyleFromToml(NixShell, k);};
  if ((k = theme->get_table("Duration"))){getStyleFromToml(Duration, k);};
}
