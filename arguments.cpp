#include "arguments.hpp"
#include <stdlib.h>

Arguments DefaultArgs = Arguments();

Arguments::Arguments(std::shared_ptr<cpptoml::table> args)
{
    TermWidth            = args->get_as<int>("TermWidth").value_or(0);
    CwdMaxDepth          = args->get_as<int>("CwdMaxDepth").value_or(0);
    CwdMaxDirSize        = args->get_as<int>("CwdMaxDirSize").value_or(0);
    MaxWidthRatio        = args->get_as<int>("MaxWidthRatio").value_or(0);
    TruncateSegmentWidth = args->get_as<int>("TruncateSegmentWidth").value_or(0);
    ColorizeHostname     = args->get_as<bool>("ColorizeHostname").value_or(false);
    NumericExitCodes     = args->get_as<bool>("NumericExitCodes").value_or(false);
    ShortenGKENames      = args->get_as<bool>("ShortenGKENames").value_or(false);
    GitMode              = strdup(args->get_as<std::string>("GitMode").value_or("simple").c_str());
    CwdMode              = strdup(args->get_as<std::string>("CwdMode").value_or("simple").c_str());
    Symbols              = strdup(args->get_as<std::string>("Symbols").value_or("curvy").c_str());
    Shell                = strdup(args->get_as<std::string>("Shell").value_or("bash").c_str());
    Modules              = strdup(args->get_as<std::string>("Modules").value_or("user,host,ssh,perms,pwd,git,jobs,root,exit").c_str());
    IgnoreRepos          = strdup(args->get_as<std::string>("IgnoreRepos").value_or("").c_str());
    PathAliases          = strdup(args->get_as<std::string>("PathAliases").value_or("").c_str());
    Duration             = strdup(args->get_as<std::string>("Duration").value_or("").c_str());
    Segments             = *args->get_array_of<std::string>("Segments");
};

// void
// Arguments::parse(std::shared_ptr<cpptoml::table> args)
// {
//     TermWidth     = args->get_as<int>("TermWidth").value_or(TermWidth);
//     CwdMaxDepth   = args->get_as<int>("CwdMaxDepth").value_or(CwdMaxDepth);
//     CwdMaxDirSize = args->get_as<int>("CwdMaxDirSize").value_or(CwdMaxDirSize);
//     MaxWidthRatio = args->get_as<int>("MaxWidthRatio").value_or(MaxWidthRatio);
//     TruncateSegmentWidth = args->get_as<int>("TruncateSegmentWidth").value_or(TruncateSegmentWidth);
//     ColorizeHostname = args->get_as<bool>("ColorizeHostname").value_or(ColorizeHostname);
//     NumericExitCodes = args->get_as<bool>("NumericExitCodes").value_or(NumericExitCodes);
//     ShortenGKENames = args->get_as<bool>("ShortenGKENames").value_or(ShortenGKENames);
//     GitMode = args->get_as<std::string>("GitMode").value_or(GitMode);
//     CwdMode = args->get_as<std::string>("CwdMode").value_or(CwdMode);
//     Symbols = args->get_as<std::string>("Symbols").value_or(Symbols);
//     Shell = args->get_as<std::string>("Shell").value_or(Shell);
//     Modules = args->get_as<std::string>("Modules").value_or(Modules);
//     // Segments = args->get_as<std::string>("Segments").value_or(Segments);
//     IgnoreRepos = args->get_as<std::string>("IgnoreRepos").value_or(IgnoreRepos);
//     PathAliases = args->get_as<std::string>("PathAliases").value_or(PathAliases);
//     Duration = args->get_as<std::string>("Duration").value_or(Duration);
// };
