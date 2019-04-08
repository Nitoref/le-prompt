#include <unordered_map> 
#include "../segments.hpp"



static const
std::unordered_map<int, std::string> signal_map
{
    {   1      ,     "ERROR"},
    {   2      ,     "USAGE"},
    { 126      ,    "NOPERM"},
    { 127      ,  "NOTFOUND"},
    { 128 +  1 ,    "SIGHUP"},
    { 128 +  2 ,    "SIGINT"},
    { 128 +  3 ,   "SIGQUIT"},
    { 128 +  4 ,    "SIGILL"},
    { 128 +  5 ,   "SIGTRAP"},
    { 128 +  6 ,   "SIGABRT"},
    { 128 +  7 ,    "SIGEMT"},
    { 128 +  8 ,    "SIGFPE"},
    { 128 +  9 ,   "SIGKILL"},
    { 128 + 10 ,    "SIGBUS"},
    { 128 + 11 ,   "SIGSEGV"},
    { 128 + 12 ,    "SIGSYS"},
    { 128 + 13 ,   "SIGPIPE"},
    { 128 + 14 ,   "SIGALRM"},
    { 128 + 15 ,   "SIGTERM"},
    { 128 + 16 ,    "SIGURG"},
    { 128 + 17 ,   "SIGSTOP"},
    { 128 + 18 ,   "SIGTSTP"},
    { 128 + 19 ,   "SIGCONT"},
    { 128 + 20 ,   "SIGCHLD"},
    { 128 + 21 ,   "SIGTTIN"},
    { 128 + 22 ,   "SIGTTOU"},
    { 128 + 23 ,     "SIGIO"},
    { 128 + 24 ,   "SIGXCPU"},
    { 128 + 25 ,   "SIGXFSZ"},
    { 128 + 26 , "SIGVTALRM"},
    { 128 + 27 ,   "SIGPROF"},
    { 128 + 28 ,  "SIGWINCH"},
    { 128 + 29 ,   "SIGINFO"},
};

MultiSegment
SegmentExit(PromptConfig p)
{
    Segment segment;
    int error = p.shell.prev_error_;
    
    if (!error) {
        return {segment};
    }
    if (p.args.numeric_exit_codes) {
        segment.content = std::to_string(error);
    }
    else
    if (auto signal = signal_map.find(error); signal != signal_map.end()) {
        segment.content = signal->second;
    }
    else {
        segment.content = std::to_string(error);
    }
    
    segment.style = p.theme.cmd_failed;
    return {segment};
};
