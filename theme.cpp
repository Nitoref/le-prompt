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
  if ((i = symbols -> get_as<std::string>("Lock")))          { lock    = strdup(i->c_str());};
  if ((i = symbols -> get_as<std::string>("Network")))       { network = strdup(i->c_str());};
  if ((i = symbols -> get_as<std::string>("Separator")))     { separator = strdup(i->c_str());};
  if ((i = symbols -> get_as<std::string>("Separator")))     { separator = strdup(i->c_str());};
  if ((i = symbols -> get_as<std::string>("SeparatorThin"))) { separator_thin = strdup(i->c_str());};
  if ((i = symbols -> get_as<std::string>("RSeparator")))    { r_separator = strdup(i->c_str());};
  if ((i = symbols -> get_as<std::string>("RSeparatorThin"))){ r_separator_thin = strdup(i->c_str());};
  if ((i = symbols -> get_as<std::string>("GitBranch")))     { git_branch   = strdup(i->c_str());};
  if ((i = symbols -> get_as<std::string>("GitDetached")))   { git_detached = strdup(i->c_str());};
  if ((i = symbols -> get_as<std::string>("GitAhead")))      { git_ahead  = strdup(i->c_str());};
  if ((i = symbols -> get_as<std::string>("GitBehind")))     { git_behind = strdup(i->c_str());};
  if ((i = symbols -> get_as<std::string>("GitStaged")))     { git_staged = strdup(i->c_str());};
  if ((i = symbols -> get_as<std::string>("GitNotStaged")))  { git_not_staged  = strdup(i->c_str());};
  if ((i = symbols -> get_as<std::string>("GitConflicted"))) { git_conflicted = strdup(i->c_str());};
  if ((i = symbols -> get_as<std::string>("GitUntracked")))  { git_untracked  = strdup(i->c_str());};
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
  if ((k = theme->get_table("Separator"))){get_style_from_toml(separator, k);};
  if ((k = theme->get_table("Username"))){get_style_from_toml(username, k);};
  if ((k = theme->get_table("UsernameRoot"))){get_style_from_toml(username_root, k);};
  if ((k = theme->get_table("Hostname"))){get_style_from_toml(hostname, k);};
  if ((k = theme->get_table("Home"))){get_style_from_toml(home, k);};
  if ((k = theme->get_table("Path"))){get_style_from_toml(path, k);};
  if ((k = theme->get_table("Cwd"))){get_style_from_toml(cwd, k);};
  if ((k = theme->get_table("Readonly"))){get_style_from_toml(readonly, k);};
  if ((k = theme->get_table("Ssh"))){get_style_from_toml(ssh, k);};
  if ((k = theme->get_table("DockerMachine"))){get_style_from_toml(docker_machine, k);};
  if ((k = theme->get_table("KubeCluster"))){get_style_from_toml(kubeCluster, k);};
  if ((k = theme->get_table("KubeNamespace"))){get_style_from_toml(kube_namespace, k);};
  if ((k = theme->get_table("DotEnv"))){get_style_from_toml(do_tEnv, k);};
  if ((k = theme->get_table("Aws"))){get_style_from_toml(aws, k);};
  if ((k = theme->get_table("RepoClean"))){get_style_from_toml(repo_clean, k);};
  if ((k = theme->get_table("RepoDirty"))){get_style_from_toml(repo_dirty, k);};
  if ((k = theme->get_table("Jobs"))){get_style_from_toml(jobs, k);};
  if ((k = theme->get_table("CmdPassed"))){get_style_from_toml(cmd_passed, k);};
  if ((k = theme->get_table("CmdFailed"))){get_style_from_toml(cmd_failed, k);};
  if ((k = theme->get_table("SvnChanges"))){get_style_from_toml(svn_changes, k);};
  if ((k = theme->get_table("GitAhead"))){get_style_from_toml(git_ahead, k);};
  if ((k = theme->get_table("GitBehind"))){get_style_from_toml(git_behind, k);};
  if ((k = theme->get_table("GitStaged"))){get_style_from_toml(git_staged, k);};
  if ((k = theme->get_table("GitNotStaged"))){get_style_from_toml(git_not_staged, k);};
  if ((k = theme->get_table("GitUntracked"))){get_style_from_toml(git_untracked, k);};
  if ((k = theme->get_table("GitConflicted"))){get_style_from_toml(git_conflicted, k);};
  if ((k = theme->get_table("GitStashed"))){get_style_from_toml(git_stashed, k);};
  if ((k = theme->get_table("VirtualEnv"))){get_style_from_toml(virtual_env, k);};
  if ((k = theme->get_table("VirtualGo"))){get_style_from_toml(virtual_go, k);};
  if ((k = theme->get_table("Perlbrew"))){get_style_from_toml(perlbrew, k);};
  if ((k = theme->get_table("TFWs"))){get_style_from_toml(TFWs, k);};
  if ((k = theme->get_table("Time"))){get_style_from_toml(time, k);};
  if ((k = theme->get_table("ShellVar"))){get_style_from_toml(shell_var, k);};
  if ((k = theme->get_table("Node"))){get_style_from_toml(node, k);};
  if ((k = theme->get_table("Load"))){get_style_from_toml(load, k);};
  if ((k = theme->get_table("NixShell"))){get_style_from_toml(nix_shell, k);};
  if ((k = theme->get_table("Duration"))){get_style_from_toml(duration, k);};
}
