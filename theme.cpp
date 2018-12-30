#include "theme.hpp"


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


const Symbols CurvySymbols =
{

              .Lock = "\uE0A2",
           .Network = "\uE0A2",
         .Separator = "\uE0B4",
     .SeparatorThin = "\uE0B5",

         .GitBranch = "\uE0A0",
       .GitDetached = "\u27A6",

          .GitAhead = "\u2B06",
         .GitBehind = "\u2B07",
         .GitStaged = "\u2714",
      .GitNotStaged = "\u270E",
     .GitConflicted = "\u273C",
      .GitUntracked = "\u2026",
};


const Symbols AnglySymbols =
{

              .Lock = "\uE0A2",
           .Network = "\uE0A2",
         .Separator = "\uE0B0",
     .SeparatorThin = "\uE0B1",

         .GitBranch = "\uE0A0",
       .GitDetached = "\u27A6",

          .GitAhead = "\u2B06",
         .GitBehind = "\u2B07",
         .GitStaged = "\u2714",
      .GitNotStaged = "\u270E",
     .GitConflicted = "\u273C",
      .GitUntracked = "\u2026",
};

const Symbols FlatSymbols =
{

             .Lock = "\uE0A2",
          .Network = "\uE0A2",
        .Separator = "\u259B",
    .SeparatorThin = "",  

        .GitBranch = "⇢",
      .GitDetached = "⇤",
 
         .GitAhead = "\u2B06",
        .GitBehind = "\u2B07",
        .GitStaged = "\u2714",
     .GitNotStaged = "\u270E",
    .GitConflicted = "\u273C",
     .GitUntracked = "+",
};


const Theme Default = 
{
    .Separator         = { 15 } ,
    .Username          = { 250 , 240},
    .UsernameRoot      = { 250 , 124},
    .Hostname          = { 250 , 238},
    .Home              = { 15  , 31},
    .Path              = { 250 , 237},
    .Cwd               = { 254 , 237},
    .Readonly          = { 254 , 124},
    .Ssh               = { 254 , 166},
    .DockerMachine     = { 177 , 55},
    .KubeCluster       = { 117 , 26},
    .KubeNamespace     = { 170 , 17},
    .DotEnv            = { 15  , 55},
    .Aws               = { 15  , 22},
    .RepoClean         = { 0   , 148},
    .RepoDirty         = { 15  , 161},
    .Jobs              = { 39  , 238},
    .CmdPassed         = { 15  , 236},
    .CmdFailed         = { 15  , 161},
    .SvnChanges        = { 22  , 148},
    .GitAhead          = { 250 , 240},
    .GitBehind         = { 250 , 240},
    .GitStaged         = { 15  , 22},
    .GitNotStaged      = { 15  , 130},
    .GitUntracked      = { 15  , 52},
    .GitConflicted     = { 15  , 9},
    .GitStashed        = { 15  , 20},
    .VirtualEnv        = { 0   , 35},
    .VirtualGo         = { 0   , 35},
    .Perlbrew          = { 0   , 20},
    .TFWs              = { 15  , 26},
    .Time              = { 15  , 236},
    .ShellVar          = { 52  , 11},
    .Node              = { 15  , 40},
    .Load              = { 15  , 22},
    .NixShell          = { 0   , 69},
    .Duration          = { 250 , 237},
};

const Theme LowContrast = 
{
    .Separator         = { 15 },
    .Username          = { 234, 250},
    .UsernameRoot      = { 234, 198},
    .Hostname          = { 234, 252},
    .Home              = { 30,  15},
    .Path              = { 234, 254},
    .Cwd               = { 236, 254}, 
    .Readonly          = { 124, 253},
    .Ssh               = { 166, 254},
    .DockerMachine     = { 55,  177},
    .KubeCluster       = { 117, 26},
    .KubeNamespace     = { 170, 17},
    .DotEnv            = { 15,  55},
//  .Aws                = { ?,  ?},
    .RepoClean         = { 232, 230},
    .RepoDirty         = { 232, 223},
    .Jobs              = { 238, 39},
    .CmdPassed         = { 18,  7},
    .CmdFailed         = { 254, 124},
    .SvnChanges        = { 148, 22},
    .GitAhead          = { 240, 250},
    .GitBehind         = { 240, 251},
    .GitStaged         = { 22,  15},
    .GitNotStaged      = { 130, 15},
    .GitUntracked      = { 52,  15},
    .GitConflicted     = { 9,   15},
    .GitStashed        = { 15,  20},
    .VirtualEnv        = { 35,  254},
    .VirtualGo         = { 35,  254},
    .Perlbrew          = { 20,  15},
    .TFWs              = { 15,  26},
    .Time              = { 236, 15},
//  .ShellVar          = { ?,   ?},
//  .Node              = { ?,   ?},
    .Load              = { 15,  22},
    .NixShell          = { 69,  254},
//  .Duration          = { ?,   ?},
};

const Theme SolarizedDark16  = 
{
    .Separator         = { 15 },
    .Username          = { 15,  4},
    .UsernameRoot      = { 15,  1},
    .Hostname          = { 15,  0},
    .Home              = { 15,  4},
    .Path              = { 15,  10},
    .Cwd               = { 15,  10},  
    .Readonly          = { 8,   1},
    .Ssh               = { 8,   9},
    .DockerMachine     = { 13,  55},
//  .KubeCluster       = { ?, ?},
//  .KubeNamespace     = { ?, ?},
    .DotEnv            = { 15,  55},
//  .Aws               = { ?,   ?},
    .RepoClean         = { 15,  3},
    .RepoDirty         = { 15,  5},
    .Jobs              = { 4,   0},
    .CmdPassed         = { 15,  0},
    .CmdFailed         = { 15,  5},
    .SvnChanges        = { 2,   3},
    .GitAhead          = { 14,  10},
    .GitBehind         = { 14,  10},
    .GitStaged         = { 15,  2},
    .GitNotStaged      = { 15,  9},
    .GitUntracked      = { 15,  1},
    .GitConflicted     = { 15,  1},
    .GitStashed        = { 15,  4},
    .VirtualEnv        = { 8,   6},
    .VirtualGo         = { 8,   6},
    .Perlbrew          = { 8,   4},
//  .TFWs              = { ?,    ?},
    .Time              = { 15,  0},
    .ShellVar          = { 1,   11},
    .Node              = { 15,  40},
    .Load              = { 15,  2},
    .NixShell          = { 0,   4},
//  .fg[_Duration]     = { ?, ?}
};

const Theme SolarizedLight16 = 
{
    .Separator         = { 15 },
    .Username          = { 15,  4},
    .UsernameRoot      = { 15,  1},
    .Hostname          = { 15,  7},
    .Home              = { 15,  4},
    .Path              = { 15,  10},
    .Cwd               = { 15,  10},  
    .Readonly          = { 8,   1},
    .Ssh               = { 8,   9},
    .DockerMachine     = { 13,  55},
//  .KubeCluster       = { ?,   ?},
//  .KubeNamespace     = { ?,   ?},
    .DotEnv            = { 15,  55},
//  .Aws               = { ?,   ?},
    .RepoClean         = { 15,  3},
    .RepoDirty         = { 15,  5},
    .Jobs              = { 4,   0},
    .CmdPassed         = { 10,  7},
    .CmdFailed         = { 15,  5},
    .SvnChanges        = { 2,   3},
    .GitAhead          = { 14,  10},
    .GitBehind         = { 14,  10},
    .GitStaged         = { 15,  2},
    .GitNotStaged      = { 15,  9},
    .GitUntracked      = { 15,  1},
    .GitConflicted     = { 15,  1},
    .GitStashed        = { 15,  4},
    .VirtualEnv        = { 8,   6},
    .VirtualGo         = { 8,   6},
    .Perlbrew          = { 8,   4},
//  .TFWs              = { ?,   ?},
    .Time              = { 15,  0},
    .ShellVar          = { 1,   11},
    .Node              = { 15,  40},
    .Load              = { 15,  2},
    .NixShell          = { 0,   7},
//  .Duration          = { ?,   ?},
};

// void to_json(json& j, const Style& s) {
//     j = json{{"fg", s.fg}, {"bg", s.bg}, {"opt", s.opt}};
// }

// void from_json(const json& j, Style& s) {
//     j.at("fg").get<int>();
//     j.at("bg").get<int>();
//     j.at("opt").get<text_style>();
// }

//     void to_json(json& j, const Theme& t) {
//         j = json {
//             {"Separator"     , t.Separator},
//             {"Username"      , t.Username},
//             {"UsernameRoot"  , t.UsernameRoot},
//             {"Hostname"      , t.Hostname},
//             {"Home"          , t.Home},
//             {"Path"          , t.Path},
//             {"Cwd"           , t.Cwd},
//             {"Readonly"      , t.Readonly},
//             {"Ssh"           , t.Ssh},
//             {"DockerMachine" , t.DockerMachine},
//             {"KubeCluster"   , t.KubeCluster},
//             {"KubeNamespace" , t.KubeNamespace},
//             {"DotEnv"        , t.DotEnv},
//             {"Aws"           , t.Aws},
//             {"RepoClean"     , t.RepoClean},
//             {"RepoDirty"     , t.RepoDirty},
//             {"Jobs"          , t.Jobs},
//             {"CmdPassed"     , t.CmdPassed},
//             {"CmdFailed"     , t.CmdFailed},
//             {"SvnChanges"    , t.SvnChanges},
//             {"GitAhead"      , t.GitAhead},
//             {"GitBehind"     , t.GitBehind},
//             {"GitStaged"     , t.GitStaged},
//             {"GitNotStaged"  , t.GitNotStaged},
//             {"GitUntracked"  , t.GitUntracked},
//             {"GitConflicted" , t.GitConflicted},
//             {"GitStashed"    , t.GitStashed},
//             {"VirtualEnv"    , t.VirtualEnv},
//             {"VirtualGo"     , t.VirtualGo},
//             {"Perlbrew"      , t.Perlbrew},
//             {"TFWs"          , t.TFWs},
//             {"Time"          , t.Time},
//             {"ShellVar"      , t.ShellVar},
//             {"Node"          , t.Node},
//             {"Load"          , t.Load},
//             {"NixShell"      , t.NixShell},
//             {"Duration"      , t.Duration},
//         };
//     }

//     void from_json(const json& j, Style& s) {
//         j.at("Separator").get_to(t.Separator);
//         j.at("Username").get_to(t.Username);
//         j.at("UsernameRoot").get_to(t.UsernameRoot);
//         j.at("Hostname").get_to(t.Hostname);
//         j.at("Home").get_to(t.Home);
//         j.at("Path").get_to(t.Path);
//         j.at("Cwd").get_to(t.Cwd);
//         j.at("Readonly").get_to(t.Readonly);
//         j.at("Ssh").get_to(t.Ssh);
//         j.at("DockerMachine").get_to(t.DockerMachine);
//         j.at("KubeCluster").get_to(t.KubeCluster);
//         j.at("KubeNamespace").get_to(t.KubeNamespace);
//         j.at("DotEnv").get_to(t.DotEnv);
//         j.at("Aws").get_to(t.Aws);
//         j.at("RepoClean").get_to(t.RepoClean);
//         j.at("RepoDirty").get_to(t.RepoDirty);
//         j.at("Jobs").get_to(t.Jobs);
//         j.at("CmdPassed").get_to(t.CmdPassed);
//         j.at("CmdFailed").get_to(t.CmdFailed);
//         j.at("SvnChanges").get_to(t.SvnChanges);
//         j.at("GitAhead").get_to(t.GitAhead);
//         j.at("GitBehind").get_to(t.GitBehind);
//         j.at("GitStaged").get_to(t.GitStaged);
//         j.at("GitNotStaged").get_to(t.GitNotStaged);
//         j.at("GitUntracked").get_to(t.GitUntracked);
//         j.at("GitConflicted").get_to(t.GitConflicted);
//         j.at("GitStashed").get_to(t.GitStashed);
//         j.at("VirtualEnv").get_to(t.VirtualEnv);
//         j.at("VirtualGo").get_to(t.VirtualGo);
//         j.at("Perlbrew").get_to(t.Perlbrew);
//         j.at("TFWs").get_to(t.TFWs);
//         j.at("Time").get_to(t.Time);
//         j.at("ShellVar").get_to(t.ShellVar);
//         j.at("Node").get_to(t.Node);
//         j.at("Load").get_to(t.Load);
//         j.at("NixShell").get_to(t.NixShell);
//         j.at("Duration").get_to(t.Duration);
//     }