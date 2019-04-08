
// #include <set>
// #include "../segments.hpp"
// #include "../utils.hpp"



// const std::string git_status_cmd =
// "git status "
// "-b "
// "--porcelain "
// "--ignore-submodules "
// "2> /dev/null";



// struct GitStatus
// {
//     string name;
//     size_t ahead      = 0;
//     size_t behind     = 0;
//     size_t staged     = 0;
//     size_t not_staged = 0;
//     size_t untracked  = 0;
//     size_t conflicted = 0;

//     void parse_branch(std::string line)
//     {
//         name = line;
//         name.pop_back();
//     }

//     void parse_line(std::string line)
//     {
//         if (line.length() < 2)
//             return;
        
//         auto code = line.substr(0, 2);
//         if (code == "??")
//             untracked++;

//         else if (code == "DD" || code == "AU" || code == "UD" || code == "UA" ||
//                  code == "DU" || code == "AA" || code == "UU" )
//             conflicted++;

//         else if (code[0] == ' ')
//             staged++;

//         else if (code[1] == ' ')
//             not_staged++;
//     }

//     GitStatus () = default;
//     GitStatus (std::string cmd)
//     {
//         auto output = exec (cmd);
//         if (output.empty())
//             return;

//         parse_branch(output.front());

//         output.pop_front();
//         for (auto& line: output)
//             parse_line(line);
//     }

// };


// void
// SegmentGit::make()
// {
//     segment.style = opt.theme.repo_clean;

//     GitStatus status (git_status_cmd);
//     // GitStatus a ("git rev-parse --show-toplevel");
//     // GitStatus b ("git rev-parse --short HEAD ");
//     // GitStatus c ("git status --porcelain");

//     if (status.name.empty())
//     {
//         return;
//     }

//     segment.content = opt.symbols.git_branch;
//     segment.content += ' ';
//     segment.content += status.name;

//     if (  status.ahead     || status.behind
//        || status.staged    || status.not_staged
//        || status.untracked || status.conflicted
//     ){
//         segment.style = opt.theme.repo_dirty;
//         if (opt.args.git_mode != "simple")
//         	return;

//         if (status.ahead){
//             segment.content += ' ';
//         	segment.content += std::to_string(status.ahead);
//             segment.content += opt.symbols.git_ahead;
//         }
//         if (status.behind){
//             segment.content += ' ';
//         	segment.content += std::to_string(status.behind);
//             segment.content += opt.symbols.git_behind;
//         }
//         if (status.staged){
//             segment.content += ' ';
//         	segment.content += std::to_string(status.staged);
//             segment.content += opt.symbols.git_staged;
//         }
//         if (status.not_staged){
//             segment.content += ' ';
//         	segment.content += std::to_string(status.not_staged);
//             segment.content += opt.symbols.git_not_staged;
//         }
//         if (status.untracked){
//             segment.content += ' ';
//         	segment.content += std::to_string(status.untracked);
//             segment.content += opt.symbols.git_untracked;
//         }
//         if (status.conflicted){
//             segment.content += ' ';
//         	segment.content += std::to_string(status.conflicted);
//             segment.content += opt.symbols.git_conflicted;
//         }
//     }
// };
