#ifndef STRING_H
#define STRING_H

class string : public std::string {
    using std::string::string;
public:
    string(const char* c):std::string(c ? c: "")
    {};
};

#endif
