#include "Parse_JSON.hpp"

void from_json(const nlohmann::json& j, Style& s)
{
    if ( auto i = j.find("fg"); i != j.end()) {s.fg = i->get<int>();};
    if ( auto i = j.find("bg"); i != j.end()) {s.bg = i->get<int>();};
}

void from_json(const nlohmann::json& j, Theme& t)
{
  if (auto i = j.find("separator")      ; i != j.end()) {t.separator      = i->get<Style>(); };
  if (auto i = j.find("username")       ; i != j.end()) {t.username       = i->get<Style>(); };
  if (auto i = j.find("username_root")  ; i != j.end()) {t.username_root  = i->get<Style>(); };
  if (auto i = j.find("hostname")       ; i != j.end()) {t.hostname       = i->get<Style>(); };
  if (auto i = j.find("home")           ; i != j.end()) {t.home           = i->get<Style>(); };
  if (auto i = j.find("path")           ; i != j.end()) {t.path           = i->get<Style>(); };
  if (auto i = j.find("cwd")            ; i != j.end()) {t.cwd            = i->get<Style>(); };
  if (auto i = j.find("readonly")       ; i != j.end()) {t.readonly       = i->get<Style>(); };
  if (auto i = j.find("ssh")            ; i != j.end()) {t.ssh            = i->get<Style>(); };
  if (auto i = j.find("docker_machine") ; i != j.end()) {t.docker_machine = i->get<Style>(); };
  if (auto i = j.find("kube_cluster")   ; i != j.end()) {t.kube_cluster   = i->get<Style>(); };
  if (auto i = j.find("kube_namespace") ; i != j.end()) {t.kube_namespace = i->get<Style>(); };
  if (auto i = j.find("dot_env")        ; i != j.end()) {t.dot_env        = i->get<Style>(); };
  if (auto i = j.find("aws")            ; i != j.end()) {t.aws            = i->get<Style>(); };
  if (auto i = j.find("repo_clean")     ; i != j.end()) {t.repo_clean     = i->get<Style>(); };
  if (auto i = j.find("repo_dirty")     ; i != j.end()) {t.repo_dirty     = i->get<Style>(); };
  if (auto i = j.find("jobs")           ; i != j.end()) {t.jobs           = i->get<Style>(); };
  if (auto i = j.find("cmd_passed")     ; i != j.end()) {t.cmd_passed     = i->get<Style>(); };
  if (auto i = j.find("cmd_failed")     ; i != j.end()) {t.cmd_failed     = i->get<Style>(); };
  if (auto i = j.find("svn_changes")    ; i != j.end()) {t.svn_changes    = i->get<Style>(); };
  if (auto i = j.find("git_ahead")      ; i != j.end()) {t.git_ahead      = i->get<Style>(); };
  if (auto i = j.find("git_behind")     ; i != j.end()) {t.git_behind     = i->get<Style>(); };
  if (auto i = j.find("git_staged")     ; i != j.end()) {t.git_staged     = i->get<Style>(); };
  if (auto i = j.find("git_not_staged") ; i != j.end()) {t.git_not_staged = i->get<Style>(); };
  if (auto i = j.find("git_untracked")  ; i != j.end()) {t.git_untracked  = i->get<Style>(); };
  if (auto i = j.find("git_conflicted") ; i != j.end()) {t.git_conflicted = i->get<Style>(); };
  if (auto i = j.find("git_stashed")    ; i != j.end()) {t.git_stashed    = i->get<Style>(); };
  if (auto i = j.find("virtual_env")    ; i != j.end()) {t.virtual_env    = i->get<Style>(); };
  if (auto i = j.find("virtual_go")     ; i != j.end()) {t.virtual_go     = i->get<Style>(); };
  if (auto i = j.find("perlbrew")       ; i != j.end()) {t.perlbrew       = i->get<Style>(); };
  if (auto i = j.find("TFWs")           ; i != j.end()) {t.TFWs           = i->get<Style>(); };
  if (auto i = j.find("time")           ; i != j.end()) {t.time           = i->get<Style>(); };
  if (auto i = j.find("shell_var")      ; i != j.end()) {t.shell_var      = i->get<Style>(); };
  if (auto i = j.find("node")           ; i != j.end()) {t.node           = i->get<Style>(); };
  if (auto i = j.find("load")           ; i != j.end()) {t.load           = i->get<Style>(); };
  if (auto i = j.find("nix_shell")      ; i != j.end()) {t.nix_shell      = i->get<Style>(); };
  if (auto i = j.find("duration")       ; i != j.end()) {t.duration       = i->get<Style>(); };
}

void from_json(const nlohmann::json& j, Symbols& s)
{
  if (auto i = j.find("lock")             ; i != j.end()) { s.lock             = i->get<std::string>(); };
  if (auto i = j.find("network")          ; i != j.end()) { s.network          = i->get<std::string>(); };
  if (auto i = j.find("separator")        ; i != j.end()) { s.separator        = i->get<std::string>(); };
  if (auto i = j.find("separator")        ; i != j.end()) { s.separator        = i->get<std::string>(); };
  if (auto i = j.find("separator_thin")   ; i != j.end()) { s.separator_thin   = i->get<std::string>(); };
  if (auto i = j.find("r_separator")      ; i != j.end()) { s.r_separator      = i->get<std::string>(); };
  if (auto i = j.find("r_separator_thin") ; i != j.end()) { s.r_separator_thin = i->get<std::string>(); };
  if (auto i = j.find("git_branch")       ; i != j.end()) { s.git_branch       = i->get<std::string>(); };
  if (auto i = j.find("git_detached")     ; i != j.end()) { s.git_detached     = i->get<std::string>(); };
  if (auto i = j.find("git_ahead")        ; i != j.end()) { s.git_ahead        = i->get<std::string>(); };
  if (auto i = j.find("git_behind")       ; i != j.end()) { s.git_behind       = i->get<std::string>(); };
  if (auto i = j.find("git_staged")       ; i != j.end()) { s.git_staged       = i->get<std::string>(); };
  if (auto i = j.find("git_not_staged")   ; i != j.end()) { s.git_not_staged   = i->get<std::string>(); };
  if (auto i = j.find("git_conflicted")   ; i != j.end()) { s.git_conflicted   = i->get<std::string>(); };
  if (auto i = j.find("git_untracked")    ; i != j.end()) { s.git_untracked    = i->get<std::string>(); };
};


void from_json(const nlohmann::json& j, Arguments& a)
{
    if ( auto i = j.find("term_width");          i != j.end()) { a.term_width         = i->get<int>();};
    if ( auto i = j.find("cwd_max_depth");       i != j.end()) { a.cwd_max_depth      = i->get<int>();};
    if ( auto i = j.find("cwd_max_dir_size");    i != j.end()) { a.cwd_max_dir_size   = i->get<int>();};
    if ( auto i = j.find("max_width_ratio");     i != j.end()) { a.max_width_ratio    = i->get<int>();};
    if ( auto i = j.find("max_segment_width");   i != j.end()) { a.max_segment_width  = i->get<int>();};
    if ( auto b = j.find("colorize_hostname");   b != j.end()) { a.colorize_hostname  = b->get<bool>();};
    if ( auto b = j.find("numeric_exit_codes");  b != j.end()) { a.numeric_exit_codes = b->get<bool>();};
    if ( auto b = j.find("shorten_g_k_e_names"); b != j.end()) { a.shorten_gke_names  = b->get<bool>();};
    if ( auto s = j.find("git_mode");            s != j.end()) { a.git_mode     = s->get<std::string>();};
    if ( auto s = j.find("cwd_mode");            s != j.end()) { a.cwd_mode     = s->get<std::string>();};
    if ( auto s = j.find("shell");               s != j.end()) { a.shell        = s->get<std::string>();};
    if ( auto s = j.find("ignore_repos");        s != j.end()) { a.ignore_repos = s->get<std::string>();};
    if ( auto s = j.find("duration");            s != j.end()) { a.duration     = s->get<std::string>();};
    if ( auto v = j.find("path_aliases");        v != j.end()) { a.path_aliases = v->get<std::map<std::string, std::string>>();};
    if ( auto o = j.find("segments"); o != j.end()){
      if ( auto v = o->find("left");  v != o->end()) { a.left_segments  = v->get<std::vector<std::string>>();};
      if ( auto v = o->find("right"); v != o->end()) { a.right_segments = v->get<std::vector<std::string>>();};
    }
}
