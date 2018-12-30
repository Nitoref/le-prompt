#include "../segments.hpp"


std::map<int, std::string> signalMap
{
    {         1,     "ERROR"},
    {         2,     "USAGE"},
    {       126,    "NOPERM"},
    {       127,  "NOTFOUND"},
    {   1 + 128,    "SIGHUP"},   // hangup
    {   2 + 128,    "SIGINT"},   // interrupt
    {   3 + 128,   "SIGQUIT"},   // quit
    {   4 + 128,    "SIGILL"},   // illegal instruction (not reset when caught)
    {   5 + 128,   "SIGTRAP"},   // trace trap (not reset when caught)
    {   6 + 128,   "SIGABRT"},   // abort()
    {   7 + 128,    "SIGEMT"},   // EMT instruction
    {   8 + 128,    "SIGFPE"},   // floating point exception
    {   9 + 128,   "SIGKILL"},   // kill (cannot be caught or ignored)
    {  10 + 128,    "SIGBUS"},   // bus error
    {  11 + 128,   "SIGSEGV"},   // segmentation violation
    {  12 + 128,    "SIGSYS"},   // bad argument to system call
    {  13 + 128,   "SIGPIPE"},   // write on a pipe with no one to read it
    {  14 + 128,   "SIGALRM"},   // alarm clock
    {  15 + 128,   "SIGTERM"},   // software termination signal from kill
    {  16 + 128,    "SIGURG"},   // urgent condition on IO channel
    {  17 + 128,   "SIGSTOP"},   // sendable stop signal not from tty
    {  18 + 128,   "SIGTSTP"},   // stop signal from tty
    {  19 + 128,   "SIGCONT"},   // continue a stopped process
    {  20 + 128,   "SIGCHLD"},   // to parent on child stop or exit
    {  21 + 128,   "SIGTTIN"},   // to readers pgrp upon background tty read
    {  22 + 128,   "SIGTTOU"},   // like TTIN for output if (tp->t_local&LTOSTOP)
    {  23 + 128,     "SIGIO"},   // input/output possible signal
    {  24 + 128,   "SIGXCPU"},   // exceeded CPU time limit
    {  25 + 128,   "SIGXFSZ"},   // exceeded file size limit
    {  26 + 128, "SIGVTALRM"},   // virtual time alarm
    {  27 + 128,   "SIGPROF"},   // profiling time alarm
    {  28 + 128,  "SIGWINCH"},   // window size changes
    {  29 + 128,   "SIGINFO"},   // information request
};

Segment* segmentExit(PromptOpt *p)
{
    char* meaning;
    if (p->args->PrevError == 0)
        return NULL;

    if (p->args->NumericExitCodes)
        asprintf(&meaning, "%d", p->args->PrevError);
    else
        try {
            meaning = strdup(signalMap.at(p->args->PrevError).c_str());
        } catch (...) {
            return NULL;
        }
    return new Segment(meaning, p->theme->CmdFailed);
}
