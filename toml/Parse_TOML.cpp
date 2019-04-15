// auto config = cpptoml::parse_file(argv[4]);
// if (auto a = config->get_table("args"))
//     toml_get_arguments(a, args);
// if (auto s = config->get_table("symbols"))
//     toml_get_symbols(s, symbols);
// if (auto t = config->get_table("theme"))
//     toml_get_theme(t, theme);



// #include "Parse_TOML.hpp"

// void toml_get_style(std::shared_ptr<cpptoml::table> k, Style& s)
// {
//   if (cpptoml::option<int> i = k->get_as<int>("fg")) {s.fg = *i;}
//   if (cpptoml::option<int> i = k->get_as<int>("bg")) {s.bg = *i;}
// }

// void toml_get_theme(std::shared_ptr<cpptoml::table> theme, Theme& t)
// {
//   std::shared_ptr<cpptoml::table> k;
//   if (( k = theme -> get_table("separator")))      { toml_get_style (k, t.separator);};
//   if (( k = theme -> get_table("username")))       { toml_get_style (k, t.username);};
//   if (( k = theme -> get_table("username_root")))  { toml_get_style (k, t.username_root);};
//   if (( k = theme -> get_table("hostname")))       { toml_get_style (k, t.hostname);};
//   if (( k = theme -> get_table("home")))           { toml_get_style (k, t.home);};
//   if (( k = theme -> get_table("path")))           { toml_get_style (k, t.path);};
//   if (( k = theme -> get_table("cwd")))            { toml_get_style (k, t.cwd);};
//   if (( k = theme -> get_table("readonly")))       { toml_get_style (k, t.readonly);};
//   if (( k = theme -> get_table("ssh")))            { toml_get_style (k, t.ssh);};
//   if (( k = theme -> get_table("docker_machine"))) { toml_get_style (k, t.docker_machine);};
//   if (( k = theme -> get_table("kube_cluster")))   { toml_get_style (k, t.kube_cluster);};
//   if (( k = theme -> get_table("kube_namespace"))) { toml_get_style (k, t.kube_namespace);};
//   if (( k = theme -> get_table("dot_env")))        { toml_get_style (k, t.dot_env);};
//   if (( k = theme -> get_table("aws")))            { toml_get_style (k, t.aws);};
//   if (( k = theme -> get_table("repo_clean")))     { toml_get_style (k, t.repo_clean);};
//   if (( k = theme -> get_table("repo_dirty")))     { toml_get_style (k, t.repo_dirty);};
//   if (( k = theme -> get_table("jobs")))           { toml_get_style (k, t.jobs);};
//   if (( k = theme -> get_table("exit_success")))   { toml_get_style (k, t.exit_success);};
//   if (( k = theme -> get_table("exit_failure")))   { toml_get_style (k, t.exit_failure);};
//   if (( k = theme -> get_table("svn_changes")))    { toml_get_style (k, t.svn_changes);};
//   if (( k = theme -> get_table("git_ahead")))      { toml_get_style (k, t.git_ahead);};
//   if (( k = theme -> get_table("git_behind")))     { toml_get_style (k, t.git_behind);};
//   if (( k = theme -> get_table("git_staged")))     { toml_get_style (k, t.git_staged);};
//   if (( k = theme -> get_table("git_not_staged"))) { toml_get_style (k, t.git_not_staged);};
//   if (( k = theme -> get_table("git_untracked")))  { toml_get_style (k, t.git_untracked);};
//   if (( k = theme -> get_table("git_conflicted"))) { toml_get_style (k, t.git_conflicted);};
//   if (( k = theme -> get_table("git_stashed")))    { toml_get_style (k, t.git_stashed);};
//   if (( k = theme -> get_table("virtual_env")))    { toml_get_style (k, t.virtual_env);};
//   if (( k = theme -> get_table("virtual_go")))     { toml_get_style (k, t.virtual_go);};
//   if (( k = theme -> get_table("perlbrew")))       { toml_get_style (k, t.perlbrew);};
//   if (( k = theme -> get_table("TFWs")))           { toml_get_style (k, t.TFWs);};
//   if (( k = theme -> get_table("time")))           { toml_get_style (k, t.time);};
//   if (( k = theme -> get_table("shell_var")))      { toml_get_style (k, t.shell_var);};
//   if (( k = theme -> get_table("node")))           { toml_get_style (k, t.node);};
//   if (( k = theme -> get_table("load")))           { toml_get_style (k, t.load);};
//   if (( k = theme -> get_table("nix_shell")))      { toml_get_style (k, t.nix_shell);};
//   if (( k = theme -> get_table("duration")))       { toml_get_style (k, t.duration);};
// }


// void toml_get_symbols(std::shared_ptr<cpptoml::table> symbols, Symbols& s)
// {
//   cpptoml::option<std::string> o;
//   if (( o = symbols -> get_as<std::string>("Lock")))          { s.lock = *o;};
//   if (( o = symbols -> get_as<std::string>("Network")))       { s.network = *o;};
//   if (( o = symbols -> get_as<std::string>("Separator")))     { s.separator = *o;};
//   if (( o = symbols -> get_as<std::string>("Separator")))     { s.separator = *o;};
//   if (( o = symbols -> get_as<std::string>("SeparatorThin"))) { s.separator_thin = *o;};
//   if (( o = symbols -> get_as<std::string>("RSeparator")))    { s.r_separator = *o;};
//   if (( o = symbols -> get_as<std::string>("RSeparatorThin"))){ s.r_separator_thin = *o;};
//   if (( o = symbols -> get_as<std::string>("GitBranch")))     { s.git_branch = *o;};
//   if (( o = symbols -> get_as<std::string>("GitDetached")))   { s.git_detached = *o;};
//   if (( o = symbols -> get_as<std::string>("GitAhead")))      { s.git_ahead = *o;};
//   if (( o = symbols -> get_as<std::string>("GitBehind")))     { s.git_behind = *o;};
//   if (( o = symbols -> get_as<std::string>("GitStaged")))     { s.git_staged = *o;};
//   if (( o = symbols -> get_as<std::string>("GitNotStaged")))  { s.git_not_staged = *o;};
//   if (( o = symbols -> get_as<std::string>("GitConflicted"))) { s.git_conflicted = *o;};
//   if (( o = symbols -> get_as<std::string>("GitUntracked")))  { s.git_untracked = *o;};
// };


// void toml_get_arguments(std::shared_ptr<cpptoml::table> args, Arguments& a)
// {
//     // cpptoml::option<int> i;
//     // cpptoml::option<bool> b;
//     // cpptoml::option<std::string> s;
//     if ( auto i = args -> get_as<int>  ("TermWidth"))          {a.term_width          = *i;};
//     if ( auto i = args -> get_as<int>  ("CwdMaxDepth"))        {a.cwd_max_depth       = *i;};
//     if ( auto i = args -> get_as<int>  ("CwdMaxDirSize"))      {a.cwd_max_dir_size    = *i;};
//     if ( auto i = args -> get_as<int>  ("MaxWidthRatio"))      {a.max_width_ratio     = *i;};
//     if ( auto i = args -> get_as<int>  ("MaxSegmentWidth"))    {a.max_segment_width   = *i;};
//     if ( auto b = args -> get_as<bool> ("ColorizeHostname"))   {a.colorize_hostname   = *b;};
//     if ( auto b = args -> get_as<bool> ("NumericExitCodes"))   {a.numeric_exit_codes  = *b;};
//     if ( auto b = args -> get_as<bool> ("ShortenGKENames"))    {a.shorten_gke_names   = *b;};
//     if ( auto s = args -> get_as<std::string> ("GitMode"))     {a.git_mode            = *s;};
//     if ( auto s = args -> get_as<std::string> ("CwdMode"))     {a.cwd_mode            = *s;};
//     if ( auto s = args -> get_as<std::string> ("Shell"))       {a.shell               = *s;};
//     if ( auto s = args -> get_as<std::string> ("IgnoreRepos")) {a.ignore_repos        = *s;};
//     if ( auto s = args -> get_as<std::string> ("Duration"))    {a.duration            = *s;};
//     if ( auto v = args -> get_array_of<std::string>("LeftSegments")){a.left_segments  = *v;};
//     if ( auto v = args -> get_array_of<std::string>("RightSegments")){a.right_segments = *v;};

//     if (auto p = args -> get_table_array("PathAliases")){
//         for (auto &k : *p){
//             for (const auto& i : *k){
//                 std::string key {i.first};
//                 std::string value = *k->get_as<std::string>(key);
//                 a.path_aliases.emplace(key, value);
//             }
//         }
//     };
// };
