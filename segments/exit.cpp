#include <unordered_map> 
#include "../modules.hpp"



static const std::unordered_map<int, std::string> signalMap
{
    {   1      ,     "ERROR"},
    {   2      ,     "USAGE"},
    { 126      ,    "NOPERM"},
    { 127      ,  "NOTFOUND"},
    { 128 +  1 ,    "SIGHUP"},   // hangup
    { 128 +  2 ,    "SIGINT"},   // interrupt
    { 128 +  3 ,   "SIGQUIT"},   // quit
    { 128 +  4 ,    "SIGILL"},   // illegal instruction (not reset when caught)
    { 128 +  5 ,   "SIGTRAP"},   // trace trap (not reset when caught)
    { 128 +  6 ,   "SIGABRT"},   // abort()
    { 128 +  7 ,    "SIGEMT"},   // EMT instruction
    { 128 +  8 ,    "SIGFPE"},   // floating point exception
    { 128 +  9 ,   "SIGKILL"},   // kill (cannot be caught or ignored)
    { 128 + 10 ,    "SIGBUS"},   // bus error
    { 128 + 11 ,   "SIGSEGV"},   // segmentation violation
    { 128 + 12 ,    "SIGSYS"},   // bad argument to system call
    { 128 + 13 ,   "SIGPIPE"},   // write on a pipe with no one to read it
    { 128 + 14 ,   "SIGALRM"},   // alarm clock
    { 128 + 15 ,   "SIGTERM"},   // software termination signal from kill
    { 128 + 16 ,    "SIGURG"},   // urgent condition on IO channel
    { 128 + 17 ,   "SIGSTOP"},   // sendable stop signal not from tty
    { 128 + 18 ,   "SIGTSTP"},   // stop signal from tty
    { 128 + 19 ,   "SIGCONT"},   // continue a stopped process
    { 128 + 20 ,   "SIGCHLD"},   // to parent on child stop or exit
    { 128 + 21 ,   "SIGTTIN"},   // to readers pgrp upon background tty read
    { 128 + 22 ,   "SIGTTOU"},   // like TTIN for output if (tp->t_local&LTOSTOP)
    { 128 + 23 ,     "SIGIO"},   // input/output possible signal
    { 128 + 24 ,   "SIGXCPU"},   // exceeded CPU time limit
    { 128 + 25 ,   "SIGXFSZ"},   // exceeded file size limit
    { 128 + 26 , "SIGVTALRM"},   // virtual time alarm
    { 128 + 27 ,   "SIGPROF"},   // profiling time alarm
    { 128 + 28 ,  "SIGWINCH"},   // window size changes
    { 128 + 29 ,   "SIGINFO"},   // information request
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
            segment.content = strdup(signalMap.at(error).c_str());
        }
        catch (...)
        {
            return;
        }
    }
    segment.style = opt.theme.CmdFailed;
};
