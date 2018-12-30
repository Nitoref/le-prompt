#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char* strnrchr(char *s, int c, int n)
{
    if (s != NULL)
        for (int i = strlen(s); i >= 0; i--)
            if (s[i] == c)
                if (n-- == 0)
                    return &s[i];
    return NULL;
}

void strrepl(char *str, const char *a, const char *b) {
    if (a != NULL && b != NULL)
        for (char *cursor = str; (cursor = strstr(cursor, a)) != NULL;){
            memmove(cursor + strlen(b), cursor + strlen(a), strlen(cursor) - strlen(a) + 1);
            for (int i = 0; b[i] != '\0'; i++)
                cursor[i] = b[i];
            cursor += strlen(b);
        }
}

char* astrrepl(const char *str, const char *a, const char *b) {
    char* strd = strdup(str);
    for (char *cursor = strd; (cursor = strstr(cursor, a)) != NULL;){
        memmove(cursor + strlen(b), cursor + strlen(a), strlen(cursor) - strlen(a) + 1);
        for (int i = 0; b[i] != '\0'; i++)
            cursor[i] = b[i];
        cursor += strlen(b);
    }
    return strd;
}

void prepend(char* str, const char *s)
{
    memmove(str + strlen(s), str, strlen(str) + 1);
    for (int i = 0; s[i] != '\0'; i++)
       str[i] = s[i];
}
