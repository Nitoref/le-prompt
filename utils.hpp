#ifndef UTILS_H
#define UTILS_H


char* strnrchr(const char *s, int c, int n);
char* astrrepl(const char *str, const char *a, const char *b);
char* astrrepl2(const char *str, const char *a, const char *b);
void  strrepl(char *str, const char *a, const char *b);
void  prepend(char* str, const char *s);

std::string exec(const char* cmd);
char* getCommandOutput(const char* input);


#endif
