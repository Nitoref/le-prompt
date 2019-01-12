#ifndef ARGUMENTS_H
#define ARGUMENTS_H

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
     int MaxSegmentWidth  = 0;
    bool ColorizeHostname = false;
    bool NumericExitCodes = false;
    bool ShortenGKENames  = false;
    const char* GitMode   = "simple";
    const char* CwdMode   = "simple";
    const char* Shell     = NULL;
    const char* IgnoreRepos = NULL;
    const char* Duration = NULL;
    std::vector<std::string> LeftSegments = {"user","host","pwd","root","exit"};
    std::vector<std::string> RightSegments = {"git"};
    std::vector<std::pair<std::string, std::string>> PathAliases;
};

extern Arguments DefaultArgs;

#endif
