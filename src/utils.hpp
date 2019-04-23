#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>


namespace utils
{

std::vector<std::string>
exec(const std::string& cmd);

size_t
term_width();

inline std::string
string(const char* s) {return s ? s : "";}

size_t
strlen(const char * s_);

size_t
strlen(std::string s);


void
strrepl(std::string& where, std::string what, std::string with);

void
str_prepend(std::string& where, std::string what);

void
str_append(std::string& where, std::string what);

}


#endif
