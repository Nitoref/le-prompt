#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <json.hpp>
#include "string.hpp"
#include "arguments.hpp"
#include "theme.hpp"


void from_json(const nlohmann::json& j, Style& s);
void from_json(const nlohmann::json& j, Theme& t);
void from_json(const nlohmann::json& j, Symbols& s);
void from_json(const nlohmann::json& j, Arguments& a);


#endif