#include "arguments.hpp"
#include <stdlib.h>

Arguments DefaultArgs =
{
               .GitMode = "compact",
               .CwdMode = "plain",
           .CwdMaxDepth = 0,
         .CwdMaxDirSize = 0,
      .ColorizeHostname = 0,
        .EastAsianWidth = 0,
                  .Mode = NULL,
                 .Shell = "bash",
               .Modules = "user,host,ssh,perms,pwd,git,jobs,root,exit",
    .MaxWidthPercentage = 0,
  .TruncateSegmentWidth = 0,
             .PrevError = 0,
      .NumericExitCodes = 0,
           .IgnoreRepos = NULL,
       .ShortenGKENames = 0,
           .PathAliases = NULL,
              .Duration = NULL,
             .TermWidth = 0,
};
