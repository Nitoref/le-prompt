#include "parse_JSON.hpp"
#include "utils.hpp"
#include <string>


// void from_json(const nlohmann::json& j, std::unordered_map<std::string, std::function<MultiSegment(PromptConfig)>>& m)
// {
// 	std::string command;
// 	Style style;

// 	if (j.is_object())
// 	{
// 		for (auto& [name, segment]: j.items())
// 		{
// 			if (auto l = segment.find("command"); l != segment.end())
// 			{
// 				command = l->get<std::string>();
// 			}
// 			else continue;

// 			if (auto l = segment.find("style"); l != segment.end())
// 			{
// 				style = l->get<Style>();
// 			}
// 			else continue;

// 			m.emplace ( name, [=](PromptConfig p) -> MultiSegment {
// 				auto result = utils::exec(command);
// 				if (!result.empty()) {
// 					utils::string::replace_all(result[0], "\n", "");
// 					return {Segment {result[0], style}};
// 				}
// 				return {Segment{}};
// 			});
// 		}
// 	}
// }


void from_json(const nlohmann::json& j, Style& s)
{
	if ( auto k = j.find("fg"); k != j.end()) {s.fg = k->get<int>();};
	if ( auto k = j.find("bg"); k != j.end()) {s.bg = k->get<int>();};
}

void from_json(const nlohmann::json& j, Theme& t)
{
	if (auto k = j.find("separator")      ; k != j.end()) {t.separator      = k->get<Style>(); };
	if (auto k = j.find("username")       ; k != j.end()) {t.username       = k->get<Style>(); };
	if (auto k = j.find("username_root")  ; k != j.end()) {t.username_root  = k->get<Style>(); };
	if (auto k = j.find("hostname")       ; k != j.end()) {t.hostname       = k->get<Style>(); };
	if (auto k = j.find("home")           ; k != j.end()) {t.home           = k->get<Style>(); };
	if (auto k = j.find("path")           ; k != j.end()) {t.path           = k->get<Style>(); };
	if (auto k = j.find("cwd")            ; k != j.end()) {t.cwd            = k->get<Style>(); };
	if (auto k = j.find("readonly")       ; k != j.end()) {t.readonly       = k->get<Style>(); };
	if (auto k = j.find("ssh")            ; k != j.end()) {t.ssh            = k->get<Style>(); };
	if (auto k = j.find("docker_machine") ; k != j.end()) {t.docker_machine = k->get<Style>(); };
	if (auto k = j.find("kube_cluster")   ; k != j.end()) {t.kube_cluster   = k->get<Style>(); };
	if (auto k = j.find("kube_namespace") ; k != j.end()) {t.kube_namespace = k->get<Style>(); };
	if (auto k = j.find("dot_env")        ; k != j.end()) {t.dot_env        = k->get<Style>(); };
	if (auto k = j.find("aws")            ; k != j.end()) {t.aws            = k->get<Style>(); };
	if (auto k = j.find("repo_clean")     ; k != j.end()) {t.repo_clean     = k->get<Style>(); };
	if (auto k = j.find("repo_dirty")     ; k != j.end()) {t.repo_dirty     = k->get<Style>(); };
	if (auto k = j.find("jobs")           ; k != j.end()) {t.jobs           = k->get<Style>(); };
	if (auto k = j.find("cmd_passed")     ; k != j.end()) {t.cmd_passed     = k->get<Style>(); };
	if (auto k = j.find("cmd_failed")     ; k != j.end()) {t.cmd_failed     = k->get<Style>(); };
	if (auto k = j.find("svn_changes")    ; k != j.end()) {t.svn_changes    = k->get<Style>(); };
	if (auto k = j.find("git_ahead")      ; k != j.end()) {t.git_ahead      = k->get<Style>(); };
	if (auto k = j.find("git_behind")     ; k != j.end()) {t.git_behind     = k->get<Style>(); };
	if (auto k = j.find("git_staged")     ; k != j.end()) {t.git_staged     = k->get<Style>(); };
	if (auto k = j.find("git_not_staged") ; k != j.end()) {t.git_not_staged = k->get<Style>(); };
	if (auto k = j.find("git_untracked")  ; k != j.end()) {t.git_untracked  = k->get<Style>(); };
	if (auto k = j.find("git_conflicted") ; k != j.end()) {t.git_conflicted = k->get<Style>(); };
	if (auto k = j.find("git_stashed")    ; k != j.end()) {t.git_stashed    = k->get<Style>(); };
	if (auto k = j.find("virtual_env")    ; k != j.end()) {t.virtual_env    = k->get<Style>(); };
	if (auto k = j.find("virtual_go")     ; k != j.end()) {t.virtual_go     = k->get<Style>(); };
	if (auto k = j.find("perlbrew")       ; k != j.end()) {t.perlbrew       = k->get<Style>(); };
	if (auto k = j.find("TFWs")           ; k != j.end()) {t.TFWs           = k->get<Style>(); };
	if (auto k = j.find("time")           ; k != j.end()) {t.time           = k->get<Style>(); };
	if (auto k = j.find("shell_var")      ; k != j.end()) {t.shell_var      = k->get<Style>(); };
	if (auto k = j.find("node")           ; k != j.end()) {t.node           = k->get<Style>(); };
	if (auto k = j.find("load")           ; k != j.end()) {t.load           = k->get<Style>(); };
	if (auto k = j.find("nix_shell")      ; k != j.end()) {t.nix_shell      = k->get<Style>(); };
	if (auto k = j.find("duration")       ; k != j.end()) {t.duration       = k->get<Style>(); };
}

void from_json(const nlohmann::json& j, Symbols& s)
{
	if (auto k = j.find("lock")             ; k != j.end()) { s.lock             = k->get<std::string>(); };
	if (auto k = j.find("network")          ; k != j.end()) { s.network          = k->get<std::string>(); };
	if (auto k = j.find("separator")        ; k != j.end()) { s.separator        = k->get<std::string>(); };
	if (auto k = j.find("separator")        ; k != j.end()) { s.separator        = k->get<std::string>(); };
	if (auto k = j.find("separator_thin")   ; k != j.end()) { s.separator_thin   = k->get<std::string>(); };
	if (auto k = j.find("r_separator")      ; k != j.end()) { s.r_separator      = k->get<std::string>(); };
	if (auto k = j.find("r_separator_thin") ; k != j.end()) { s.r_separator_thin = k->get<std::string>(); };
	if (auto k = j.find("git_branch")       ; k != j.end()) { s.git_branch       = k->get<std::string>(); };
	if (auto k = j.find("git_detached")     ; k != j.end()) { s.git_detached     = k->get<std::string>(); };
	if (auto k = j.find("git_ahead")        ; k != j.end()) { s.git_ahead        = k->get<std::string>(); };
	if (auto k = j.find("git_behind")       ; k != j.end()) { s.git_behind       = k->get<std::string>(); };
	if (auto k = j.find("git_staged")       ; k != j.end()) { s.git_staged       = k->get<std::string>(); };
	if (auto k = j.find("git_not_staged")   ; k != j.end()) { s.git_not_staged   = k->get<std::string>(); };
	if (auto k = j.find("git_conflicted")   ; k != j.end()) { s.git_conflicted   = k->get<std::string>(); };
	if (auto k = j.find("cwd_wrap")         ; k != j.end()) { s.cwd_wrap         = k->get<std::string>();};
	if (auto k = j.find("git_untracked")    ; k != j.end()) { s.git_untracked    = k->get<std::string>(); };
};


void from_json(const nlohmann::json& j, Arguments& a)
{
	if (auto k = j.find("cwd_max_depth");       k != j.end()) { a.cwd_max_depth      = k->get<int>();};
	if (auto k = j.find("cwd_max_depth");       k != j.end()) { a.cwd_max_depth      = k->get<int>();};
	if (auto k = j.find("cwd_max_dir_size");    k != j.end()) { a.cwd_max_dir_size   = k->get<int>();};
	if (auto k = j.find("max_width_ratio");     k != j.end()) { a.max_width_ratio    = k->get<int>();};
	if (auto k = j.find("max_segment_width");   k != j.end()) { a.max_segment_width  = k->get<int>();};
	if (auto k = j.find("colorize_hostname");   k != j.end()) { a.colorize_hostname  = k->get<bool>();};
	if (auto k = j.find("numeric_exit_codes");  k != j.end()) { a.numeric_exit_codes = k->get<bool>();};
	if (auto k = j.find("shorten_g_k_e_names"); k != j.end()) { a.shorten_gke_names  = k->get<bool>();};
	if (auto k = j.find("default_user");        k != j.end()) { a.default_user = k->get<std::string>();};
	if (auto k = j.find("default_host");        k != j.end()) { a.default_host = k->get<std::string>();};
	if (auto k = j.find("time_format");         k != j.end()) { a.time_format  = k->get<std::string>();};
	if (auto k = j.find("git_mode");            k != j.end()) { a.git_mode     = k->get<std::string>();};
	if (auto k = j.find("cwd_mode");            k != j.end()) { a.cwd_mode     = k->get<std::string>();};
	if (auto k = j.find("shell");               k != j.end()) { a.shell        = k->get<std::string>();};
	if (auto k = j.find("duration");            k != j.end()) { a.duration     = k->get<std::string>();};
	if (auto k = j.find("path_aliases");        k != j.end()) { a.path_aliases = k->get<std::map<std::string, std::string>>();};
	if (auto k = j.find("ignore_repos");        k != j.end()) { a.ignore_repos = k->get<std::vector<std::string>>();};
	if (auto o = j.find("segments"); o != j.end()){
		if (auto k = o->find("left");  k != o->end()) { a.left_segments  = k->get<std::vector<std::string>>();};
		if ( auto k = o->find("right"); k != o->end()) { a.right_segments = k->get<std::vector<std::string>>();};
	}
}
