#include "cpptoml.hpp"
#include <iostream>
#include <unordered_map>
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

std::unordered_map<std::string, std::string> m =
{
    {"Hello", "world"}
};

// int main(int argc, char const *argv[])
// {
//     auto& x = m["Jack"];
//     std::cout << x << '\n';
// }
