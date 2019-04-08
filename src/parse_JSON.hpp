#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include "segment.hpp"
#include "theme.hpp"
#include "symbols.hpp"
#include "arguments.hpp"
#include "shell_info.hpp"
#include "prompt_config.hpp"

#include <nlohmann/json.hpp>


// void from_json(const nlohmann::json& j, std::unordered_map<std::string, std::function<Segment(PromptConfig)>>& m);
void from_json(const nlohmann::json& j, Style& s);
void from_json(const nlohmann::json& j, Theme& t);
void from_json(const nlohmann::json& j, Symbols& s);
void from_json(const nlohmann::json& j, Arguments& a);


#endif
