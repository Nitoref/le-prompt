#include <stdexcept>
#include <memory>
#include <string>
#include <array>


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

std::string exec(const char* cmd) {
    std::array<char, 1024> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe)
        throw std::runtime_error("popen() failed!");

    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
        result += buffer.data();

    return result;
}

// Props to https://rosettacode.org/wiki/Get_system_command_output#C
char* getCommandOutput(const char* input)
{
    FILE *fd = popen(input, "r");
    if (!fd) return NULL;
 
    size_t charactersRead = 0;
    size_t commandAlloc   = 1024;
    size_t length         = 0;
    
    char buffer[commandAlloc];
    char *output = (char*)malloc(commandAlloc);
 
    while ((charactersRead = fread(
        buffer, 1, sizeof(buffer), fd)) != 0)
    {
        if (length + charactersRead >= commandAlloc)
        {
            commandAlloc *= 2;
            output = (char*)realloc(output, commandAlloc);
        }
        memmove(output + length, buffer, charactersRead);
        length += charactersRead;
    }
    
    if (pclose(fd) != 0 | length == 0){
        free(output);
        return NULL;
    }
    
    output[length-1] = '\0';
    return output;
}


// Props to http://www.daemonology.net/blog/2008-06-05-faster-utf8-strlen.html
#define ONEMASK ((size_t)(-1) / 0xFF)
size_t strlen_utf8(const char * s_)
{
    const char * s;
    size_t count = 0;
    size_t u;
    unsigned char b;

    /* Handle any initial misaligned bytes. */
    for (s = s_; (uintptr_t)(s) & (sizeof(size_t) - 1); s++) {
        b = *s;

        /* Exit if we hit a zero byte. */
        if (b == '\0')
            goto done;

        /* Is this byte NOT the first byte of a character? */
        count += (b >> 7) & ((~b) >> 6);
    }

    /* Handle complete blocks. */
    for (; ; s += sizeof(size_t)) {
        /* Prefetch 256 bytes ahead. */
        __builtin_prefetch(&s[256], 0, 0);

        /* Grab 4 or 8 bytes of UTF-8 data. */
        u = *(size_t *)(s);

        /* Exit the loop if there are any zero bytes. */
        if ((u - ONEMASK) & (~u) & (ONEMASK * 0x80))
            break;

        /* Count bytes which are NOT the first byte of a character. */
        u = ((u & (ONEMASK * 0x80)) >> 7) & ((~u) >> 6);
        count += (u * ONEMASK) >> ((sizeof(size_t) - 1) * 8);
    }

    /* Take care of any left-over bytes. */
    for (; ; s++) {
        b = *s;

        /* Exit if we hit a zero byte. */
        if (b == '\0')
            break;

        /* Is this byte NOT the first byte of a character? */
        count += (b >> 7) & ((~b) >> 6);
    }

    done:
    return ((s - s_) - count);
}
