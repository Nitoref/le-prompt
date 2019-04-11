#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include "modules.hpp"

#include "arguments.hpp"
#include "symbols.hpp"
#include "theme.hpp"
#include "shell.hpp"

#include <nlohmann/json.hpp>


void from_json(const nlohmann::json& j, Style& s);
void from_json(const nlohmann::json& j, Theme& t);
void from_json(const nlohmann::json& j, Symbols& s);
void from_json(const nlohmann::json& j, Arguments& a);


#endif
