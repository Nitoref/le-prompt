
#ifndef TOML_PARSER_H
#define TOML_PARSER_H

#include "config.hpp"

#include <string>
#include <cpptoml.hpp>

namespace toml
{

void parse(Config& config, std::string filename);

void get_style(std::shared_ptr<cpptoml::table> k, Style& s);
void get_theme(std::shared_ptr<cpptoml::table> conf, Theme& t);
void get_symbols(std::shared_ptr<cpptoml::table> conf, Symbols& s);
void get_arguments(std::shared_ptr<cpptoml::table> conf, Arguments& a);
void get_segments(std::shared_ptr<cpptoml::table> args, Arguments& a);
void get_extensions(std::shared_ptr<cpptoml::table_array> extensions);

}


#endif
