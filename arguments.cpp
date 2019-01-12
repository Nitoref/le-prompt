#include "arguments.hpp"
#include <stdlib.h>
#include <iostream> //////////
#include <sstream>

Arguments::Arguments(std::shared_ptr<cpptoml::table> conf)
{
  auto args = conf->get_table("args");
  if ((!args))
    return;

  if ( auto i = args -> get_as<int>  ("TermWidth"))          {term_width         = *i;};
  if ( auto i = args -> get_as<int>  ("CwdMaxDepth"))        {cwd_max_depth       = *i;};
  if ( auto i = args -> get_as<int>  ("CwdMaxDirSize"))      {cwd_max_dir_size     = *i;};
  if ( auto i = args -> get_as<int>  ("MaxWidthRatio"))      {max_width_ratio     = *i;};
  if ( auto i = args -> get_as<int>  ("MaxSegmentWidth"))    {max_segment_width   = *i;};
  if ( auto b = args -> get_as<bool> ("ColorizeHostname"))   {colorize_hostname  = *b;};
  if ( auto b = args -> get_as<bool> ("NumericExitCodes"))   {numeric_exit_codes  = *b;};
  if ( auto b = args -> get_as<bool> ("ShortenGKENames"))    {shorten_gke_names   = *b;};
  if ( auto s = args -> get_as<std::string> ("GitMode"))     {git_mode     = strdup(s->c_str());};
  if ( auto s = args -> get_as<std::string> ("CwdMode"))     {cwd_mode     = strdup(s->c_str());};
  if ( auto s = args -> get_as<std::string> ("Shell"))       {shell       = strdup(s->c_str());};
  if ( auto s = args -> get_as<std::string> ("IgnoreRepos")) {ignore_repos = strdup(s->c_str());};
  if ( auto s = args -> get_as<std::string> ("Duration"))    {duration    = strdup(s->c_str());};
  if ( auto a = args -> get_array_of<std::string>("LeftSegments")){left_segments  = *a;};
  if ( auto a = args -> get_array_of<std::string>("RightSegments")){right_segments = *a;};

  if (auto p = args -> get_table_array("PathAliases")){
    for (auto &k : *p){
      for (const auto& i : *k){
        std::string key (i.first);
        std::string value = *k->get_as<std::string>(key);
        path_aliases.emplace_back(key, value);
      }
    }
  };
};
