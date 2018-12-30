#include <fstream>
#include "theme.hpp"
#include "include/json.hpp"

using json = nlohmann::json;


Theme parseTheme(char *file)
{
    Theme theme;
    
    std::ifstream i("theme.json");
    json j;
    i >> j;

    

    // theme.Separator.fg     = j["Separator"]["fg"]     ?: Default.Separator.fg;
    // theme.Username.fg      = j["Username"]["fg"]      ?: Default.Username.fg;
    // theme.UsernameRoot.fg  = j["UsernameRoot"]["fg"]  ?: Default.UsernameRoot.fg;
    // theme.Hostname.fg      = j["Hostname"]["fg"]      ?: Default.Hostname.fg;
    // theme.Home.fg          = j["Home"]["fg"]          ?: Default.Home.fg;
    // theme.Path.fg          = j["Path"]["fg"]          ?: Default.Path.fg;
    // theme.Cwd.fg           = j["Cwd"]["fg"]           ?: Default.Cwd.fg;
    // theme.Readonly.fg      = j["Readonly"]["fg"]      ?: Default.Readonly.fg;
    // theme.Ssh.fg           = j["Ssh"]["fg"]           ?: Default.Ssh.fg;
    // theme.DockerMachine.fg = j["DockerMachine"]["fg"] ?: Default.DockerMachine.fg;
    // theme.KubeCluster.fg   = j["KubeCluster"]["fg"]   ?: Default.KubeCluster.fg;
    // theme.KubeNamespace.fg = j["KubeNamespace"]["fg"] ?: Default.KubeNamespace.fg;
    // theme.DotEnv.fg        = j["DotEnv"]["fg"]        ?: Default.DotEnv.fg;
    // theme.Aws.fg           = j["Aws"]["fg"]           ?: Default.Aws.fg;
    // theme.RepoClean.fg     = j["RepoClean"]["fg"]     ?: Default.RepoClean.fg;
    // theme.RepoDirty.fg     = j["RepoDirty"]["fg"]     ?: Default.RepoDirty.fg;
    // theme.Jobs.fg          = j["Jobs"]["fg"]          ?: Default.Jobs.fg;
    // theme.CmdPassed.fg     = j["CmdPassed"]["fg"]     ?: Default.CmdPassed.fg;
    // theme.CmdFailed.fg     = j["CmdFailed"]["fg"]     ?: Default.CmdFailed.fg;
    // theme.SvnChanges.fg    = j["SvnChanges"]["fg"]    ?: Default.SvnChanges.fg;
    // theme.GitAhead.fg      = j["GitAhead"]["fg"]      ?: Default.GitAhead.fg;
    // theme.GitBehind.fg     = j["GitBehind"]["fg"]     ?: Default.GitBehind.fg;
    // theme.GitStaged.fg     = j["GitStaged"]["fg"]     ?: Default.GitStaged.fg;
    // theme.GitNotStaged.fg  = j["GitNotStaged"]["fg"]  ?: Default.GitNotStaged.fg;
    // theme.GitUntracked.fg  = j["GitUntracked"]["fg"]  ?: Default.GitUntracked.fg;
    // theme.GitConflicted.fg = j["GitConflicted"]["fg"] ?: Default.GitConflicted.fg;
    // theme.GitStashed.fg    = j["GitStashed"]["fg"]    ?: Default.GitStashed.fg;
    // theme.VirtualEnv.fg    = j["VirtualEnv"]["fg"]    ?: Default.VirtualEnv.fg;
    // theme.VirtualGo.fg     = j["VirtualGo"]["fg"]     ?: Default.VirtualGo.fg;
    // theme.Perlbrew.fg      = j["Perlbrew"]["fg"]      ?: Default.Perlbrew.fg;
    // theme.TFWs.fg          = j["TFWs"]["fg"]          ?: Default.TFWs.fg;
    // theme.Time.fg          = j["Time"]["fg"]          ?: Default.Time.fg;
    // theme.ShellVar.fg      = j["ShellVar"]["fg"]      ?: Default.ShellVar.fg;
    // theme.Node.fg          = j["Node"]["fg"]          ?: Default.Node.fg;
    // theme.Load.fg          = j["Load"]["fg"]          ?: Default.Load.fg;
    // theme.NixShell.fg      = j["NixShell"]["fg"]      ?: Default.NixShell.fg;
    // theme.Duration.fg      = j["Duration"]["fg"]      ?: Default.Duration.fg;

    return theme;
}
