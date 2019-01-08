#include <unordered_map> 
#include "../modules.hpp"



static const
std::unordered_map<int, std::string> signalMap
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

void
SegmentExit::makeSegment()
{
    int error = opt.args.PrevError;
    if (!error)
    {
        return;
    }

    if (opt.args.NumericExitCodes)
    {
        asprintf(&segment.content, "%d", error);
    }
    else
    {
        try 
        {
            segment.content = strdup(
                signalMap.at(error).c_str()
            );
        }
        catch (...)
        {
            return;
        }
    }
    segment.style = opt.theme.CmdFailed;
};
