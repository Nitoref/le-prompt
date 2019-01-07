#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include <iostream>
#include <unordered_map>
#include "yaml.h"
#include "promptOptions.hpp"


template<>
struct YAML::convert<char*> {
  static bool decode(const Node& node, char* &str) {
    try {
      str = strdup(node.as<std::string>().c_str());
      return true;
    } catch (...) {
      std::cout << "Parsing failed" << '\n';
      return false;
    }
  }
};

template<>
struct YAML::convert<Arguments> {
  static bool decode(const Node& node, Arguments& a) {
    try {
        a.GitMode              = node["GitMode"]              ? node["GitMode"]              .as <char*>() : "simple";
        a.CwdMode              = node["CwdMode"]              ? node["CwdMode"]              .as <char*>() : "simple";
        a.CwdMaxDepth          = node["CwdMaxDepth"]          ? node["CwdMaxDepth"]          .as <int>()   : 0;
        a.CwdMaxDirSize        = node["CwdMaxDirSize"]        ? node["CwdMaxDirSize"]        .as <int>()   : 0;
        a.ColorizeHostname     = node["ColorizeHostname"]     ? node["ColorizeHostname"]     .as <bool>()  : false;
        a.Mode                 = node["Mode"]                 ? node["Mode"]                 .as <char*>() : nullptr;
        a.Shell                = node["Shell"]                ? node["Shell"]                .as <char*>() : "bash";
        a.Modules              = node["Modules"]              ? node["Modules"]              .as <char*>() : "user,host,ssh,perms,pwd,git,jobs,root,exit";
        a.MaxWidthPercentage   = node["MaxWidthPercentage"]   ? node["MaxWidthPercentage"]   .as <int>()   : 0;
        a.TruncateSegmentWidth = node["TruncateSegmentWidth"] ? node["TruncateSegmentWidth"] .as <int>()   : 0;
        a.PrevError            = node["PrevError"]            ? node["PrevError"]            .as <int>()   : 0;
        a.NumericExitCodes     = node["NumericExitCodes"]     ? node["NumericExitCodes"]     .as <bool>()  : false;
        a.IgnoreRepos          = node["IgnoreRepos"]          ? node["IgnoreRepos"]          .as <char*>() : nullptr;
        a.ShortenGKENames      = node["ShortenGKENames"]      ? node["ShortenGKENames"]      .as <bool>()  : false;
        a.PathAliases          = node["PathAliases"]          ? node["PathAliases"]          .as <char*>() : nullptr;
        a.Duration             = node["Duration"]             ? node["Duration"]             .as <char*>() : nullptr;
        a.TermWidth            = node["TermWidth"]            ? node["TermWidth"]            .as <int>()   : 0;
      return true;
    } catch (...) {
      std::cout << "parsing failed" << '\n';
      return false;
    }
  }
};

template<>
struct YAML::convert<Symbols> {
  static bool decode(const Node& node, Symbols& s) {
    try {
        s.Lock          = node["Lock"]          ? node["Lock"].as<char*>()          : "";
        s.Network       = node["Network"]       ? node["Network"].as<char*>()       : "";
        s.Separator     = node["Separator"]     ? node["Separator"].as<char*>()     : "";
        s.SeparatorThin = node["SeparatorThin"] ? node["SeparatorThin"].as<char*>() : "";
        s.GitBranch     = node["GitBranch"]     ? node["GitBranch"].as<char*>()     : "";
        s.GitDetached   = node["GitDetached"]   ? node["GitDetached"].as<char*>()   : "";
        s.GitAhead      = node["GitAhead"]      ? node["GitAhead"].as<char*>()      : "";
        s.GitBehind     = node["GitBehind"]     ? node["GitBehind"].as<char*>()     : "";
        s.GitStaged     = node["GitStaged"]     ? node["GitStaged"].as<char*>()     : "";
        s.GitNotStaged  = node["GitNotStaged"]  ? node["GitNotStaged"].as<char*>()  : "";
        s.GitConflicted = node["GitConflicted"] ? node["GitConflicted"].as<char*>() : "";
        s.GitUntracked  = node["GitUntracked"]  ? node["GitUntracked"].as<char*>()  : "";
      return true;
    } catch (...) {
      std::cout << "parsing failed" << '\n';
      return false;
    }
  }
};

template<>
struct YAML::convert<Style> {
  static bool decode(const Node& node, Style& s) {
    try {
      s.fg  = node["fg"] ? node["fg"].as<int>() : 0;
      s.bg  = node["bg"] ? node["bg"].as<int>() : 0;
      return true;
    } catch (...) {
      std::cout << "parsing failed" << '\n';
      return false;
    }
  }
};

template<>
struct YAML::convert<Theme> {
  static bool decode(const Node& node, Theme& t) {
    t.Separator     = node["Separator"]     ? node["Separator"].  as<Style>()   : Style();
    t.Username      = node["Username"]      ? node["Username"].as<Style>()      : Style();
    t.UsernameRoot  = node["UsernameRoot"]  ? node["UsernameRoot"].as<Style>()  : Style();
    t.Hostname      = node["Hostname"]      ? node["Hostname"].as<Style>()      : Style();
    t.Home          = node["Home"]          ? node["Home"].as<Style>()          : Style();
    t.Path          = node["Path"]          ? node["Path"].as<Style>()          : Style();
    t.Cwd           = node["Cwd"]           ? node["Cwd"].as<Style>()           : Style();
    t.Readonly      = node["Readonly"]      ? node["Readonly"].as<Style>()      : Style();
    t.Ssh           = node["Ssh"]           ? node["Ssh"].as<Style>()           : Style();
    t.DockerMachine = node["DockerMachine"] ? node["DockerMachine"].as<Style>() : Style();
    t.KubeCluster   = node["KubeCluster"]   ? node["KubeCluster"].as<Style>()   : Style();
    t.KubeNamespace = node["KubeNamespace"] ? node["KubeNamespace"].as<Style>() : Style();
    t.DotEnv        = node["DotEnv"]        ? node["DotEnv"].as<Style>()        : Style();
    t.Aws           = node["Aws"]           ? node["Aws"].as<Style>()           : Style();
    t.RepoClean     = node["RepoClean"]     ? node["RepoClean"].as<Style>()     : Style();
    t.RepoDirty     = node["RepoDirty"]     ? node["RepoDirty"].as<Style>()     : Style();
    t.Jobs          = node["Jobs"]          ? node["Jobs"].as<Style>()          : Style();
    t.CmdPassed     = node["CmdPassed"]     ? node["CmdPassed"].as<Style>()     : Style();
    t.CmdFailed     = node["CmdFailed"]     ? node["CmdFailed"].as<Style>()     : Style();
    t.SvnChanges    = node["SvnChanges"]    ? node["SvnChanges"].as<Style>()    : Style();
    t.GitAhead      = node["GitAhead"]      ? node["GitAhead"].as<Style>()      : Style();
    t.GitBehind     = node["GitBehind"]     ? node["GitBehind"].as<Style>()     : Style();
    t.GitStaged     = node["GitStaged"]     ? node["GitStaged"].as<Style>()     : Style();
    t.GitNotStaged  = node["GitNotStaged"]  ? node["GitNotStaged"].as<Style>()  : Style();
    t.GitUntracked  = node["GitUntracked"]  ? node["GitUntracked"].as<Style>()  : Style();
    t.GitConflicted = node["GitConflicted"] ? node["GitConflicted"].as<Style>() : Style();
    t.GitStashed    = node["GitStashed"]    ? node["GitStashed"].as<Style>()    : Style();
    t.VirtualEnv    = node["VirtualEnv"]    ? node["VirtualEnv"].as<Style>()    : Style();
    t.VirtualGo     = node["VirtualGo"]     ? node["VirtualGo"].as<Style>()     : Style();
    t.Perlbrew      = node["Perlbrew"]      ? node["Perlbrew"].as<Style>()      : Style();
    t.TFWs          = node["TFWs"]          ? node["TFWs"].as<Style>()          : Style();
    t.Time          = node["Time"]          ? node["Time"].as<Style>()          : Style();
    t.ShellVar      = node["ShellVar"]      ? node["ShellVar"].as<Style>()      : Style();
    t.Node          = node["Node"]          ? node["Node"].as<Style>()          : Style();
    t.Load          = node["Load"]          ? node["Load"].as<Style>()          : Style();
    t.NixShell      = node["NixShell"]      ? node["NixShell"].as<Style>()      : Style();
    t.Duration      = node["Duration"]      ? node["Duration"].as<Style>()      : Style();
    return true;
  }
};

#endif
