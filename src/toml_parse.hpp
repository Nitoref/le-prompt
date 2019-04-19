
#ifndef TOML_PARSER_H
#define TOML_PARSER_H

#include "config.hpp"

#include <string>
#include <cpptoml.hpp>

namespace toml
{

using string = std::string;
using table_ptr = std::shared_ptr<cpptoml::table>;

void parse(config& config, string filename);

template<class T>
void get(const table_ptr data, string key, T& t);
void get(const table_ptr data, string key, Style& style);
// template<class T>
void get(const table_ptr data, string key, std::vector<string>& t);

void get_segments   (table_ptr table, config& c);
void get_global     (table_ptr table, config& c);
void get_user       (table_ptr table, config& c);
void get_context    (table_ptr table, config& c);
void get_dir        (table_ptr table, config& c);
void get_readonly   (table_ptr table, config& c);
void get_aws        (table_ptr table, config& c);
void get_docker     (table_ptr table, config& c);
void get_git        (table_ptr table, config& c);
void get_jobs       (table_ptr table, config& c);
void get_root       (table_ptr table, config& c);
void get_status     (table_ptr table, config& c);
void get_virtual_env(table_ptr table, config& c);
void get_prompt     (table_ptr table, config& c);
void get_time       (table_ptr table, config& c);
void get_ssh        (table_ptr table, config& c);

}


#endif
