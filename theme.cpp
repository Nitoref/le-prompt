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
  if ((i = symbols -> get_as<std::string>("Lock")))          { lock    = strdup(i->data());};
  if ((i = symbols -> get_as<std::string>("Network")))       { network = strdup(i->data());};
  if ((i = symbols -> get_as<std::string>("Separator")))     { separator = strdup(i->data());};
  if ((i = symbols -> get_as<std::string>("Separator")))     { separator = strdup(i->data());};
  if ((i = symbols -> get_as<std::string>("SeparatorThin"))) { separator_thin = strdup(i->data());};
  if ((i = symbols -> get_as<std::string>("RSeparator")))    { r_separator = strdup(i->data());};
  if ((i = symbols -> get_as<std::string>("RSeparatorThin"))){ r_separator_thin = strdup(i->data());};
  if ((i = symbols -> get_as<std::string>("GitBranch")))     { git_branch   = strdup(i->data());};
  if ((i = symbols -> get_as<std::string>("GitDetached")))   { git_detached = strdup(i->data());};
  if ((i = symbols -> get_as<std::string>("GitAhead")))      { git_ahead  = strdup(i->data());};
  if ((i = symbols -> get_as<std::string>("GitBehind")))     { git_behind = strdup(i->data());};
  if ((i = symbols -> get_as<std::string>("GitStaged")))     { git_staged = strdup(i->data());};
  if ((i = symbols -> get_as<std::string>("GitNotStaged")))  { git_not_staged  = strdup(i->data());};
  if ((i = symbols -> get_as<std::string>("GitConflicted"))) { git_conflicted = strdup(i->data());};
  if ((i = symbols -> get_as<std::string>("GitUntracked")))  { git_untracked  = strdup(i->data());};
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

  std::shared_ptr<cpptoml::table> k;
  if ((k = theme->get_table("separator"))){get_style_from_toml(separator, k);};
  if ((k = theme->get_table("username"))){get_style_from_toml(username, k);};
  if ((k = theme->get_table("username_root"))){get_style_from_toml(username_root, k);};
  if ((k = theme->get_table("hostname"))){get_style_from_toml(hostname, k);};
  if ((k = theme->get_table("home"))){get_style_from_toml(home, k);};
  if ((k = theme->get_table("path"))){get_style_from_toml(path, k);};
  if ((k = theme->get_table("cwd"))){get_style_from_toml(cwd, k);};
  if ((k = theme->get_table("readonly"))){get_style_from_toml(readonly, k);};
  if ((k = theme->get_table("ssh"))){get_style_from_toml(ssh, k);};
  if ((k = theme->get_table("docker_machine"))){get_style_from_toml(docker_machine, k);};
  if ((k = theme->get_table("kube_cluster"))){get_style_from_toml(kube_cluster, k);};
  if ((k = theme->get_table("kube_namespace"))){get_style_from_toml(kube_namespace, k);};
  if ((k = theme->get_table("dot_env"))){get_style_from_toml(dot_env, k);};
  if ((k = theme->get_table("aws"))){get_style_from_toml(aws, k);};
  if ((k = theme->get_table("repo_clean"))){get_style_from_toml(repo_clean, k);};
  if ((k = theme->get_table("repo_dirty"))){get_style_from_toml(repo_dirty, k);};
  if ((k = theme->get_table("jobs"))){get_style_from_toml(jobs, k);};
  if ((k = theme->get_table("cmd_passed"))){get_style_from_toml(cmd_passed, k);};
  if ((k = theme->get_table("cmd_failed"))){get_style_from_toml(cmd_failed, k);};
  if ((k = theme->get_table("svn_changes"))){get_style_from_toml(svn_changes, k);};
  if ((k = theme->get_table("git_ahead"))){get_style_from_toml(git_ahead, k);};
  if ((k = theme->get_table("git_behind"))){get_style_from_toml(git_behind, k);};
  if ((k = theme->get_table("git_staged"))){get_style_from_toml(git_staged, k);};
  if ((k = theme->get_table("git_not_staged"))){get_style_from_toml(git_not_staged, k);};
  if ((k = theme->get_table("git_untracked"))){get_style_from_toml(git_untracked, k);};
  if ((k = theme->get_table("git_conflicted"))){get_style_from_toml(git_conflicted, k);};
  if ((k = theme->get_table("git_stashed"))){get_style_from_toml(git_stashed, k);};
  if ((k = theme->get_table("virtual_env"))){get_style_from_toml(virtual_env, k);};
  if ((k = theme->get_table("virtual_go"))){get_style_from_toml(virtual_go, k);};
  if ((k = theme->get_table("perlbrew"))){get_style_from_toml(perlbrew, k);};
  if ((k = theme->get_table("TFWs"))){get_style_from_toml(TFWs, k);};
  if ((k = theme->get_table("time"))){get_style_from_toml(time, k);};
  if ((k = theme->get_table("shell_var"))){get_style_from_toml(shell_var, k);};
  if ((k = theme->get_table("node"))){get_style_from_toml(node, k);};
  if ((k = theme->get_table("load"))){get_style_from_toml(load, k);};
  if ((k = theme->get_table("nix_shell"))){get_style_from_toml(nix_shell, k);};
  if ((k = theme->get_table("duration"))){get_style_from_toml(duration, k);};
}
