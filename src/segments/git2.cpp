// std::string also   = " && ";
// std::string except = " 2>/dev/null || ";
// std::string cancel = " exit ";

// std::string git_branch_cmd = "git symbolic-ref --short HEAD 2>/dev/null || git rev-parse --short HEAD 2>/dev/null || exit";
// std::string git_index_cmd  = "git diff-index --no-ext-diff --ignore-submodules --quiet --cached HEAD && echo 0 || echo 1";
// std::string git_files_cmd  = "git diff-files --no-ext-diff --ignore-submodules --quiet && echo 0 || echo 1";
// std::string git_untrck_cmd = "git ls-files --other --directory --exclude-standard --no-empty-directory | sed q";
// std::string git_status_cmd = git_branch_cmd + also + git_index_cmd + also + git_files_cmd;

// Module
// SegmentGit(const Config& c)
// {
//     auto status = utils::exec(git_status_cmd);
//     if (status.empty())
//     {
//         return Module{};
//     }

//     status[0].pop_back();
//     status[1].pop_back();
//     status[2].pop_back();

//     Module module;
//     module.emplace_back(
//         module::id::git_branch,
//         c.symbols.git_branch + ' ' + status[0],
//         c.theme.repo_clean
//     );

//     if (!status[1].empty()) {
//         module.emplace_back(
//             module::id::git_staged,
//             c.symbols.git_staged,
//             c.theme.git_staged
//         );
//     }

//     if (!status[2].empty()) {
//         module.emplace_back(
//             module::id::git_not_staged,
//             c.symbols.git_not_staged,
//             c.theme.git_not_staged
//         );
//     }

//     return module;
// }
