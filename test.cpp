#include "cpptoml.hpp"
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <map>
#include <future>

// #include "include/json.hpp"
// #include "yaml.h"
// using json = nlohmann::json;

// struct Album
// {
//     int albumId;
//     int id;
//     std::string title;
//     std::string url;
//     std::string thumbnailUrl;
// };

// void from_json(const json& j, Album& a) {
//     j.at("id").get_to(a.id);
//     j.at("albumId").get_to(a.albumId);
//     j.at("title").get_to(a.title);
//     j.at("url").get_to(a.url);
//     j.at("thumbnailUrl").get_to(a.thumbnailUrl);
// }

struct T {
    int x;
    int y;
};


// int main(int argc, char const *argv[])
// {
//     auto config  = cpptoml::parse_file("/Users/nitoref/Desktop/powerless/C++/test.toml");
//     auto t = config->get_table("test");
//     auto u = config->get_as<T>("test");
// //     std::cout << t->get_as<int>("x").value_or(17);
// }
