#include <iostream>

int main(int argc, char **argv, char **envp)
{
  std::string s = "hello";
  auto a = s.find("j");
  auto b = s.find(a, '/');
  s = s.substr(6);
  std::cout << b << "\n";
}
