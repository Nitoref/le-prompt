#include "theme.hpp"


ShellInfo Bash =
{
     .colorTemplate = "\\[\\e%s\\]",
     .rootIndicator = "\\$",
  .escapedBackslash = "\\\\",
   .escapedBacktick = "\\`",
     .escapedDollar = "\\$",
};

ShellInfo Zsh =
{
     .colorTemplate = "%%{\e%s%%}",
     // .colorTemplate = "%%{\u001b%s%%}",
     .rootIndicator = "%#",
  .escapedBackslash = "\\",
   .escapedBacktick = "\\`",
     .escapedDollar = "\\$",
};

ShellInfo Bare =
{
     // .colorTemplate = "%s",
     .colorTemplate = "\e%s",
     .rootIndicator = "$",
  .escapedBackslash = "\\",
   .escapedBacktick = "`",
     .escapedDollar = "$",
};


Symbols CurvySymbols =
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


// Symbols AnglySymbols =
// {

//               .Lock = "\uE0A2",
//            .Network = "\uE0A2",
//          .Separator = "\uE0B0",
//      .SeparatorThin = "\uE0B1",

//          .GitBranch = "\uE0A0",
//        .GitDetached = "\u27A6",

//           .GitAhead = "\u2B06",
//          .GitBehind = "\u2B07",
//          .GitStaged = "\u2714",
//       .GitNotStaged = "\u270E",
//      .GitConflicted = "\u273C",
//       .GitUntracked = "\u2026",
// };

// Symbols FlatSymbols =
// {

//              .Lock = "\uE0A2",
//           .Network = "\uE0A2",
//         .Separator = "\u259B",
//     .SeparatorThin = "",  

//         .GitBranch = "⇢",
//       .GitDetached = "⇤",
 
//          .GitAhead = "\u2B06",
//         .GitBehind = "\u2B07",
//         .GitStaged = "\u2714",
//      .GitNotStaged = "\u270E",
//     .GitConflicted = "\u273C",
//      .GitUntracked = "+",
// };


// Theme Default = 
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

Theme LowContrast = 
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

// Theme SolarizedDark16  = 
// {
//     .Separator         = { 15 },
//     .Username          = { 15,  4},
//     .UsernameRoot      = { 15,  1},
//     .Hostname          = { 15,  0},
//     .Home              = { 15,  4},
//     .Path              = { 15,  10},
//     .Cwd               = { 15,  10},  
//     .Readonly          = { 8,   1},
//     .Ssh               = { 8,   9},
//     .DockerMachine     = { 13,  55},
// //  .KubeCluster       = { ?, ?},
// //  .KubeNamespace     = { ?, ?},
//     .DotEnv            = { 15,  55},
// //  .Aws               = { ?,   ?},
//     .RepoClean         = { 15,  3},
//     .RepoDirty         = { 15,  5},
//     .Jobs              = { 4,   0},
//     .CmdPassed         = { 15,  0},
//     .CmdFailed         = { 15,  5},
//     .SvnChanges        = { 2,   3},
//     .GitAhead          = { 14,  10},
//     .GitBehind         = { 14,  10},
//     .GitStaged         = { 15,  2},
//     .GitNotStaged      = { 15,  9},
//     .GitUntracked      = { 15,  1},
//     .GitConflicted     = { 15,  1},
//     .GitStashed        = { 15,  4},
//     .VirtualEnv        = { 8,   6},
//     .VirtualGo         = { 8,   6},
//     .Perlbrew          = { 8,   4},
// //  .TFWs              = { ?,    ?},
//     .Time              = { 15,  0},
//     .ShellVar          = { 1,   11},
//     .Node              = { 15,  40},
//     .Load              = { 15,  2},
//     .NixShell          = { 0,   4},
// //  .fg[_Duration]     = { ?, ?}
// };

// Theme SolarizedLight16 = 
// {
//     .Separator         = { 15 },
//     .Username          = { 15,  4},
//     .UsernameRoot      = { 15,  1},
//     .Hostname          = { 15,  7},
//     .Home              = { 15,  4},
//     .Path              = { 15,  10},
//     .Cwd               = { 15,  10},  
//     .Readonly          = { 8,   1},
//     .Ssh               = { 8,   9},
//     .DockerMachine     = { 13,  55},
// //  .KubeCluster       = { ?,   ?},
// //  .KubeNamespace     = { ?,   ?},
//     .DotEnv            = { 15,  55},
// //  .Aws               = { ?,   ?},
//     .RepoClean         = { 15,  3},
//     .RepoDirty         = { 15,  5},
//     .Jobs              = { 4,   0},
//     .CmdPassed         = { 10,  7},
//     .CmdFailed         = { 15,  5},
//     .SvnChanges        = { 2,   3},
//     .GitAhead          = { 14,  10},
//     .GitBehind         = { 14,  10},
//     .GitStaged         = { 15,  2},
//     .GitNotStaged      = { 15,  9},
//     .GitUntracked      = { 15,  1},
//     .GitConflicted     = { 15,  1},
//     .GitStashed        = { 15,  4},
//     .VirtualEnv        = { 8,   6},
//     .VirtualGo         = { 8,   6},
//     .Perlbrew          = { 8,   4},
// //  .TFWs              = { ?,   ?},
//     .Time              = { 15,  0},
//     .ShellVar          = { 1,   11},
//     .Node              = { 15,  40},
//     .Load              = { 15,  2},
//     .NixShell          = { 0,   7},
// //  .Duration          = { ?,   ?},
// };
