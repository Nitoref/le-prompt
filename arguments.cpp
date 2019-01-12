#include "arguments.hpp"
#include <stdlib.h>


Arguments::Arguments(std::shared_ptr<cpptoml::table> conf)
{
  auto args = conf->get_table("args");
  if ((!args))
    return;

  cpptoml::option<int> i;  
  cpptoml::option<bool> b;  
  cpptoml::option<std::string> s;
  cpptoml::option<std::vector<std::string>> a;

  if ((i = args -> get_as<int>  ("TermWidth")))          {TermWidth         = *i;};
  if ((i = args -> get_as<int>  ("CwdMaxDepth")))        {CwdMaxDepth       = *i;};
  if ((i = args -> get_as<int>  ("CwdMaxDirSize")))      {CwdMaxDirSize     = *i;};
  if ((i = args -> get_as<int>  ("MaxWidthRatio")))      {MaxWidthRatio     = *i;};
  if ((i = args -> get_as<int>  ("MaxSegmentWidth")))    {MaxSegmentWidth   = *i;};
  if ((b = args -> get_as<bool> ("ColorizeHostname")))   {ColorizeHostname  = *b;};
  if ((b = args -> get_as<bool> ("NumericExitCodes")))   {NumericExitCodes  = *b;};
  if ((b = args -> get_as<bool> ("ShortenGKENames")))    {ShortenGKENames   = *b;};
  if ((s = args -> get_as<std::string> ("GitMode")))     {GitMode     = strdup(s->c_str());};
  if ((s = args -> get_as<std::string> ("CwdMode")))     {CwdMode     = strdup(s->c_str());};
  if ((s = args -> get_as<std::string> ("Shell")))       {Shell       = strdup(s->c_str());};
  if ((s = args -> get_as<std::string> ("IgnoreRepos"))) {IgnoreRepos = strdup(s->c_str());};
  if ((s = args -> get_as<std::string> ("Duration")))    {Duration    = strdup(s->c_str());};
  if ((a = args -> get_array_of<std::string>("LeftSegments"))){LeftSegments  = *a;};
  if ((a = args -> get_array_of<std::string>("RightSegments"))){RightSegments = *a;};
  // if ((a = args -> get_array_of<std::pair<std::string>>("PathAliases"))){Segments   = *a;};
};
