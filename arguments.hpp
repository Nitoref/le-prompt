#ifndef ARGUMENTS_H
#define ARGUMENTS_H


struct Arguments
{
    const char* GitMode;
    const char* CwdMode;
    int   CwdMaxDepth;
    int   CwdMaxDirSize;
    bool  ColorizeHostname;
    int   PromptOnNewLine;
    const char* Mode;
    const char* Shell;
    const char* Modules;
    int   MaxWidthPercentage;
    int   TruncateSegmentWidth;
    int   PrevError;
    bool  NumericExitCodes;
    const char* IgnoreRepos;
    bool  ShortenGKENames;
    const char* PathAliases;
    const char* Duration;
    int   TermWidth;
};

extern Arguments DefaultArgs;


#endif
