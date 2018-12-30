#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <map>
#include <future>

#include "include/json.hpp"
using json = nlohmann::json;


// int main(int argc, char const *argv[])
// {
//     std::ifstream i("theme.json");
//     json j;
//     i >> j;

//     int x;
//     x = j["Node"]["fg"];
//     x = j["Load"]["fg"];
//     x = j["NixShell"]["fg"];
//     x = j["Duration"]["fg"];


//     x = j["ihefiefiei"];
//     std::cout << x << '\n';
// }