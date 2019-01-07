#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <memory>
#include <string>
#include <vector>
#include "cpptoml.hpp"

struct Arguments
{
    Arguments() = default;
    Arguments(std::shared_ptr<cpptoml::table> args);
    void parse(std::shared_ptr<cpptoml::table> args);
     int TermWidth        = 0;
     int PrevError        = 0;
     int CwdMaxDepth      = 0;
     int CwdMaxDirSize    = 0;
     int MaxWidthRatio    = 0;
     int TruncateSegmentWidth = 0;
    bool ColorizeHostname = false;
    bool NumericExitCodes = false;
    bool ShortenGKENames  = false;
    const char* GitMode   = "simple";
    const char* CwdMode   = "simple";
    const char* Symbols   = "curvy";
    const char* Shell     = "bash";
    const char* Modules   = "user,host,ssh,perms,pwd,git,jobs,root,exit";
    std::vector<std::string> Segments = {"user","host","pwd","git","root","exit"};
    const char* IgnoreRepos = NULL;
    const char* PathAliases = NULL;
    const char* Duration = NULL;
};

extern Arguments DefaultArgs;

#endif
