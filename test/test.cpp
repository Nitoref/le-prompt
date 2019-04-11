#include <filesystem>
#include <iostream>
#include <list>

int main() 
{
    auto path = std::filesystem::current_path();
    std::cout << path << '\n';
}