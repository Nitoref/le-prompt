// #ifndef GIT_H
// #define GIT_H

// #include <string>
// #include <git2.h>

// #include "../modules.hpp"




// struct SegmentGit2: public ThreadedSegment
// {
//     using ThreadedSegment::ThreadedSegment;

//     struct RepoStats
//     {
//         RepoStats() = default;
//         size_t ahead      = 0;
//         size_t behind     = 0;
//         size_t staged     = 0;
//         size_t notStaged  = 0;
//         size_t untracked  = 0;
//         size_t conflicted = 0;
//     };

//     static bool set;

//     static RepoStats stats;
    
//     static char *branchName;
//     static char *repoName;
    
//     static git_repository *repo;
//     static git_reference *head;

//     int get_git_status();
//     int get_branch_name();
//     int get_ahead_behind();
//     int get_stats(git_status_list *status);

//     void make(){
//         ;
//     }
// };




// struct SegmentGitAhead: public SegmentGit2
// {
//     void make(){
//         if (!set)
//             get_git_status();
//         if (stats.ahead)
//         {
//             asprintf(&segment.content, "%s %zu", opt.symbols.GitAhead, stats.ahead);
//             segment.style = opt.theme.GitAhead;
//         }
//     };
// };

// // struct SegmentGitBehind: public SegmentGit2
// // {
// //     Segment* make(){
// //         if (stats.behind)
// //             return new Segment(std::string(opt.symbols.GitBehind) + " " +std::to_string(stats.behind));
// //     };
// // };

// // struct SegmentGitStaged: public SegmentGit2
// // {
// //     Segment* make(){
// //         if (stats.staged)
// //             return new Segment(std::string(opt.symbols.GitStaged) + " " +std::to_string(stats.staged));
// //     };
// // };

// // struct SegmentGitNotStaged: public SegmentGit2
// // {
// //     Segment* make(){
// //         if (stats.notStaged)
// //             return new Segment(std::string(opt.symbols.GitNotStaged) + " " +std::to_string(stats.notStaged));
// //     };
// // };

// // struct SegmentGitUntracked: public SegmentGit2
// // {
// //     Segment* make(){
// //         if (stats.untracked)
// //             return new Segment(std::string(opt.symbols.GitUntracked) + " " +std::to_string(stats.untracked));
// //     };
// // };

// // struct SegmentGitConflicted: public SegmentGit2
// // {
// //     Segment* make(){
// //         if (stats.Conflicted)
// //             return new Segment(std::string(opt.symbols.GitConflicted) + " " +std::to_string(stats.Conflicted));
// //     };
// // };

// #endif
