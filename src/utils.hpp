#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>

namespace utils
{

namespace string
{
std::string safe(const char* s);
void replace_all(std::string& in, const std::string& from, const std::string& to);
void prepend(std::string& where, std::string what);
void append(std::string& where, std::string what);

size_t rnfind (std::string& s, char c, size_t n);

size_t length(const char * s_);
size_t length(std::string s);
}

std::vector<std::string> exec(const std::string& cmd);
int term_width();

}

#endif
