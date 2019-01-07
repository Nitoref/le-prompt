#include "arguments.hpp"
#include <stdlib.h>

Arguments DefaultArgs =
{
               .GitMode = "simple",
               .CwdMode = "simple",
           .CwdMaxDepth = 0,
         .CwdMaxDirSize = 0,
      .ColorizeHostname = false,
                  .Mode = NULL,
                 .Shell = "bash",
               .Modules = "user,host,ssh,perms,pwd,git,jobs,root,exit",
    .MaxWidthPercentage = 0,
  .TruncateSegmentWidth = 0,
             .PrevError = 0,
      .NumericExitCodes = false,
           .IgnoreRepos = NULL,
       .ShortenGKENames = false,
           .PathAliases = NULL,
              .Duration = NULL,
             .TermWidth = 0,
};
