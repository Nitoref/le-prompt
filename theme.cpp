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


Symbols::Symbols(std::shared_ptr<cpptoml::table> syms)
{
  Lock           = strdup(syms->get_as<std::string>("Lock")          .value_or("\uE0A2").c_str());
  Network        = strdup(syms->get_as<std::string>("Network")       .value_or("\uE0A2").c_str());
  Separator      = strdup(syms->get_as<std::string>("Separator")     .value_or("\uE0B4").c_str());
  SeparatorThin  = strdup(syms->get_as<std::string>("SeparatorThin") .value_or("\uE0B5").c_str());
  GitBranch      = strdup(syms->get_as<std::string>("GitBranch")     .value_or("\uE0A0").c_str());
  GitDetached    = strdup(syms->get_as<std::string>("GitDetached")   .value_or("\u27A6").c_str());
  GitAhead       = strdup(syms->get_as<std::string>("GitAhead")      .value_or("\u2B06").c_str());
  GitBehind      = strdup(syms->get_as<std::string>("GitBehind")     .value_or("\u2B07").c_str());
  GitStaged      = strdup(syms->get_as<std::string>("GitStaged")     .value_or("\u2714").c_str());
  GitNotStaged   = strdup(syms->get_as<std::string>("GitNotStaged")  .value_or("\u270E").c_str());
  GitConflicted  = strdup(syms->get_as<std::string>("GitConflicted") .value_or("\u273C").c_str());
  GitUntracked   = strdup(syms->get_as<std::string>("GitUntracked")  .value_or("\u2026").c_str());
};


Style::Style(std::shared_ptr<cpptoml::table> style, const char* key, Style s)
{
  fg = style->get_as<int>(key).value_or(s.fg);
  bg = style->get_as<int>(key).value_or(s.bg);
}

Theme::Theme(std::shared_ptr<cpptoml::table> theme)
{
  Separator     = Style(theme, "Separator",     { 15  , 0 } );
  Username      = Style(theme, "Username",      { 250 , 240});
  UsernameRoot  = Style(theme, "UsernameRoot",  { 250 , 124});
  Hostname      = Style(theme, "Hostname",      { 250 , 238});
  Home          = Style(theme, "Home",          { 15  , 31});
  Path          = Style(theme, "Path",          { 250 , 237});
  Cwd           = Style(theme, "Cwd",           { 254 , 237});
  Readonly      = Style(theme, "Readonly",      { 254 , 124});
  Ssh           = Style(theme, "Ssh",           { 254 , 166});
  DockerMachine = Style(theme, "DockerMachine", { 177 , 55});
  KubeCluster   = Style(theme, "KubeCluster",   { 117 , 26});
  KubeNamespace = Style(theme, "KubeNamespace", { 170 , 17});
  DotEnv        = Style(theme, "DotEnv",        { 15  , 55});
  Aws           = Style(theme, "Aws",           { 15  , 22});
  RepoClean     = Style(theme, "RepoClean",     { 0   , 148});
  RepoDirty     = Style(theme, "RepoDirty",     { 15  , 161});
  Jobs          = Style(theme, "Jobs",          { 39  , 238});
  CmdPassed     = Style(theme, "CmdPassed",     { 15  , 236});
  CmdFailed     = Style(theme, "CmdFailed",     { 15  , 161});
  SvnChanges    = Style(theme, "SvnChanges",    { 22  , 148});
  GitAhead      = Style(theme, "GitAhead",      { 250 , 240});
  GitBehind     = Style(theme, "GitBehind",     { 250 , 240});
  GitStaged     = Style(theme, "GitStaged",     { 15  , 22});
  GitNotStaged  = Style(theme, "GitNotStaged",  { 15  , 130});
  GitUntracked  = Style(theme, "GitUntracked",  { 15  , 52});
  GitConflicted = Style(theme, "GitConflicted", { 15  , 9});
  GitStashed    = Style(theme, "GitStashed",    { 15  , 20});
  VirtualEnv    = Style(theme, "VirtualEnv",    { 0   , 35});
  VirtualGo     = Style(theme, "VirtualGo",     { 0   , 35});
  Perlbrew      = Style(theme, "Perlbrew",      { 0   , 20});
  TFWs          = Style(theme, "TFWs",          { 15  , 26});
  Time          = Style(theme, "Time",          { 15  , 236});
  ShellVar      = Style(theme, "ShellVar",      { 52  , 11});
  Node          = Style(theme, "Node",          { 15  , 40});
  Load          = Style(theme, "Load",          { 15  , 22});
  NixShell      = Style(theme, "NixShell",      { 0   , 69});
  Duration      = Style(theme, "Duration",      { 250 , 237});
}

// const Theme el  
// {
//     .Separator         = { 15 } ,
//     .Username          = { 250 , 240},
//     .UsernameRoot      = { 250 , 124},
//     .Hostname          = { 250 , 238},
//     .Home              = { 15  , 31},
//     .Path              = { 250 , 237},
//     .Cwd               = { 254 , 237},
//     .Readonly          = { 254 , 124},
//     .Ssh               = { 254 , 166},
//     .DockerMachine     = { 177 , 55},
//     .KubeCluster       = { 117 , 26},
//     .KubeNamespace     = { 170 , 17},
//     .DotEnv            = { 15  , 55},
//     .Aws               = { 15  , 22},
//     .RepoClean         = { 0   , 148},
//     .RepoDirty         = { 15  , 161},
//     .Jobs              = { 39  , 238},
//     .CmdPassed         = { 15  , 236},
//     .CmdFailed         = { 15  , 161},
//     .SvnChanges        = { 22  , 148},
//     .GitAhead          = { 250 , 240},
//     .GitBehind         = { 250 , 240},
//     .GitStaged         = { 15  , 22},
//     .GitNotStaged      = { 15  , 130},
//     .GitUntracked      = { 15  , 52},
//     .GitConflicted     = { 15  , 9},
//     .GitStashed        = { 15  , 20},
//     .VirtualEnv        = { 0   , 35},
//     .VirtualGo         = { 0   , 35},
//     .Perlbrew          = { 0   , 20},
//     .TFWs              = { 15  , 26},
//     .Time              = { 15  , 236},
//     .ShellVar          = { 52  , 11},
//     .Node              = { 15  , 40},
//     .Load              = { 15  , 22},
//     .NixShell          = { 0   , 69},
//     .Duration          = { 250 , 237},
// };

// const Theme LowContrast = 
// {
//     .Separator         = { 15 },
//     .Username          = { 234, 250},
//     .UsernameRoot      = { 234, 198},
//     .Hostname          = { 234, 252},
//     .Home              = { 30,  15},
//     .Path              = { 234, 254},
//     .Cwd               = { 236, 254}, 
//     .Readonly          = { 124, 253},
//     .Ssh               = { 166, 254},
//     .DockerMachine     = { 55,  177},
//     .KubeCluster       = { 117, 26},
//     .KubeNamespace     = { 170, 17},
//     .DotEnv            = { 15,  55},
// //  .Aws                = { ?,  ?},
//     .RepoClean         = { 232, 230},
//     .RepoDirty         = { 232, 223},
//     .Jobs              = { 238, 39},
//     .CmdPassed         = { 18,  7},
//     .CmdFailed         = { 254, 124},
//     .SvnChanges        = { 148, 22},
//     .GitAhead          = { 240, 250},
//     .GitBehind         = { 240, 251},
//     .GitStaged         = { 22,  15},
//     .GitNotStaged      = { 130, 15},
//     .GitUntracked      = { 52,  15},
//     .GitConflicted     = { 9,   15},
//     .GitStashed        = { 15,  20},
//     .VirtualEnv        = { 35,  254},
//     .VirtualGo         = { 35,  254},
//     .Perlbrew          = { 20,  15},
//     .TFWs              = { 15,  26},
//     .Time              = { 236, 15},
// //  .ShellVar          = { ?,   ?},
// //  .Node              = { ?,   ?},
//     .Load              = { 15,  22},
//     .NixShell          = { 69,  254},
// //  .Duration          = { ?,   ?},
// };
