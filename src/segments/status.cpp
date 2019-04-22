#include <map>
#include <string> 
#include "modules.hpp"



#ifndef _WIN32

std::string
signal_str(int code)
{
    std::map<int, std::string> signal_str_map
    {
        {  1     ,     "ERROR"},
        {  2     ,     "USAGE"},
        {126     ,    "NOPERM"},
        {127     ,  "NOTFOUND"},
        {128 +  1,    "SIGHUP"},
        {128 +  2,    "SIGINT"},
        {128 +  3,   "SIGQUIT"},
        {128 +  4,    "SIGILL"},
        {128 +  5,   "SIGTRAP"},
        {128 +  6,   "SIGABRT"},
        {128 +  7,    "SIGEMT"},
        {128 +  8,    "SIGFPE"},
        {128 +  9,   "SIGKILL"},
        {128 + 10,    "SIGBUS"},
        {128 + 11,   "SIGSEGV"},
        {128 + 12,    "SIGSYS"},
        {128 + 13,   "SIGPIPE"},
        {128 + 14,   "SIGALRM"},
        {128 + 15,   "SIGTERM"},
        {128 + 16,    "SIGURG"},
        {128 + 17,   "SIGSTOP"},
        {128 + 18,   "SIGTSTP"},
        {128 + 19,   "SIGCONT"},
        {128 + 20,   "SIGCHLD"},
        {128 + 21,   "SIGTTIN"},
        {128 + 22,   "SIGTTOU"},
        {128 + 23,     "SIGIO"},
        {128 + 24,   "SIGXCPU"},
        {128 + 25,   "SIGXFSZ"},
        {128 + 26, "SIGVTALRM"},
        {128 + 27,   "SIGPROF"},
        {128 + 28,  "SIGWINCH"},
        {128 + 29,   "SIGINFO"},
    };
    
    auto str = signal_str_map.find(code);
    
    return str != signal_str_map.end()
        ? str->second
        : std::to_string(code);
}

#endif

Module
SegmentStatus(const config& c)
{
    std::string content;

    int error  = c._meta.error;
    if (!error && !c.status.always)
    {
        return {};
    }

#ifdef _WIN32
    content = std::to_string(error);
#else
    if (c.status.numeric)
    {
        content = std::to_string(error);
    }
    else
    {
        content = signal_str(error);
    }
#endif

    return Module {
        {
            segment::id::status,
            content,
            c.status.theme_failure
        }
    };
}
