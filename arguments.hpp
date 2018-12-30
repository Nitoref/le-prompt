#ifndef ARGUMENTS_H
#define ARGUMENTS_H


struct Arguments
{
    const char* GitMode;
    const char* CwdMode;
    const int   CwdMaxDepth;
    const int   CwdMaxDirSize;
    const int   ColorizeHostname;
    const int   EastAsianWidth;
    const int   PromptOnNewLine;
    const char* Mode;
    const char* Shell;
    const char* Modules;
    const int   MaxWidthPercentage;
    const int   TruncateSegmentWidth;
    const int   PrevError;
    const int   NumericExitCodes;
    const char* IgnoreRepos;
    const int   ShortenGKENames;
    const char* PathAliases;
    const char* Duration;
    const int   TermWidth;
};

extern Arguments DefaultArgs;


#endif
