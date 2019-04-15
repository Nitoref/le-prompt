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


namespace string
{

inline std::string
safe(const char* s) {return s ? s : "";}

void
replace_all(std::string& where, const std::string what, const std::string with);
void
replace_all(std::string& where, char what, std::string with);

void
prepend(std::string& where, std::string what);

void
append(std::string& where, std::string what);


size_t
rnfind (std::string& s, char c, size_t n);

size_t
length(const char * s_);

size_t
length(std::string s);

}

}


#endif
