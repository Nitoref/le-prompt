#include "parse_JSON.hpp"
#include "utils.hpp"
#include <string>
#include <chrono>
#include <functional>
#include <unordered_map>

using str    = std::string;
using strvec = std::vector<str>;
using strmap = std::map<str, str>;

using jsonit = nlohmann::basic_json<>::iterator;


void from_json(const nlohmann::json& j, Arguments& a)
{
	if (auto k = j.find("timeout");        k != j.end()) { a.timeout        = k->get<int>();};
	if (auto k = j.find("width_limit");    k != j.end()) { a.width_limit    = k->get<int>();};
	if (auto k = j.find("padding_left");   k != j.end()) { a.padding_left   = k->get<int>();};
	if (auto k = j.find("padding_right");  k != j.end()) { a.padding_right  = k->get<int>();};
	if (auto k = j.find("padding_end");    k != j.end()) { a.padding_end    = k->get<int>();};
	if (auto k = j.find("force_newline");  k != j.end()) { a.force_newline  = k->get<bool>();};
	if (auto k = j.find("native_rprompt"); k != j.end()) { a.native_rprompt = k->get<bool>();};
	
	if (auto k = j.find("numeric_exit");  k != j.end()) { a.numeric_exit  = k->get<bool>();};
	if (auto k = j.find("jobs_count");    k != j.end()) { a.jobs_count    = k->get<bool>();};
	
	if (auto k = j.find("default_user"); k != j.end()) { a.default_user = k->get<str>();};
	if (auto k = j.find("default_host"); k != j.end()) { a.default_host = k->get<str>();};
	if (auto k = j.find("time_format");  k != j.end()) { a.time_format  = k->get<str>();};
	
	if (auto k = j.find("dir_depth");       k != j.end()) { a.dir_depth       = k->get<int>();};
	if (auto k = j.find("dir_dir_limit");   k != j.end()) { a.dir_dir_limit   = k->get<int>();};
	if (auto k = j.find("dir_fancy");       k != j.end()) { a.dir_fancy       = k->get<bool>();};

	if (auto k = j.find("git_format");  k != j.end()) { a.git_format  = k->get<str>();};
	if (auto k = j.find("git_compact"); k != j.end()) { a.git_compact = k->get<bool>();};
	if (auto k = j.find("git_count");   k != j.end()) { a.git_count   = k->get<bool>();};
	if (auto k = j.find("git_ignore");  k != j.end()) { a.git_ignore  = k->get<strvec>();};
	
	if (auto k = j.find("path_aliases");     k != j.end()) { a.path_aliases     = k->get<strmap>();};
	if (auto k = j.find("left_segments");    k != j.end()) { a.left_segments    = k->get<strvec>();};
	if (auto k = j.find("right_segments");   k != j.end()) { a.right_segments   = k->get<strvec>();};
	if (auto k = j.find("newline_segments"); k != j.end()) { a.newline_segments = k->get<strvec>();};
}

void from_json(const nlohmann::json& j, Style& s)
{
	if ( auto k = j.find("fg"); k != j.end()) {s.fg = k->get<int>();};
	if ( auto k = j.find("bg"); k != j.end()) {s.bg = k->get<int>();};
}

void from_json(const nlohmann::json& j, Theme& t)
{
	if (auto k = j.find("separator")      ; k != j.end()) {t.separator      = k->get<Style>(); };
	
	if (auto k = j.find("username")       ; k != j.end()) {t.username       = k->get<Style>(); };
	if (auto k = j.find("root")           ; k != j.end()) {t.root           = k->get<Style>(); };
	if (auto k = j.find("hostname")       ; k != j.end()) {t.hostname       = k->get<Style>(); };
	
	if (auto k = j.find("home")           ; k != j.end()) {t.home           = k->get<Style>(); };
	if (auto k = j.find("path")           ; k != j.end()) {t.path           = k->get<Style>(); };
	if (auto k = j.find("dir")            ; k != j.end()) {t.dir            = k->get<Style>(); };
	if (auto k = j.find("readonly")       ; k != j.end()) {t.readonly       = k->get<Style>(); };
	
	if (auto k = j.find("time")           ; k != j.end()) {t.time           = k->get<Style>(); };
	if (auto k = j.find("jobs")           ; k != j.end()) {t.jobs           = k->get<Style>(); };
	if (auto k = j.find("ssh")            ; k != j.end()) {t.ssh            = k->get<Style>(); };
	if (auto k = j.find("aws")            ; k != j.end()) {t.aws            = k->get<Style>(); };
	if (auto k = j.find("docker")         ; k != j.end()) {t.docker         = k->get<Style>(); };
	if (auto k = j.find("dot_env")        ; k != j.end()) {t.dot_env        = k->get<Style>(); };
	if (auto k = j.find("virtual_env")    ; k != j.end()) {t.virtual_env    = k->get<Style>(); };
	if (auto k = j.find("duration")       ; k != j.end()) {t.duration       = k->get<Style>(); };

	if (auto k = j.find("git_clean")      ; k != j.end()) {t.git_clean      = k->get<Style>(); };
	if (auto k = j.find("git_dirty")      ; k != j.end()) {t.git_dirty      = k->get<Style>(); };
	if (auto k = j.find("git_stash")      ; k != j.end()) {t.git_stash      = k->get<Style>(); };
	if (auto k = j.find("git_ahead")      ; k != j.end()) {t.git_ahead      = k->get<Style>(); };
	if (auto k = j.find("git_behind")     ; k != j.end()) {t.git_behind     = k->get<Style>(); };
	if (auto k = j.find("git_staged")     ; k != j.end()) {t.git_staged     = k->get<Style>(); };
	if (auto k = j.find("git_nstaged")    ; k != j.end()) {t.git_nstaged    = k->get<Style>(); };
	if (auto k = j.find("git_conflicted") ; k != j.end()) {t.git_conflicted = k->get<Style>(); };
	if (auto k = j.find("git_untracked")  ; k != j.end()) {t.git_untracked  = k->get<Style>(); };
	if (auto k = j.find("exit_success")   ; k != j.end()) {t.exit_success   = k->get<Style>(); };
	if (auto k = j.find("exit_failure")   ; k != j.end()) {t.exit_failure   = k->get<Style>(); };
}

void from_json(const nlohmann::json& j, Symbols& s)
{
	if (auto k = j.find("separator")   ; k != j.end()) { s.separator    = k->get<str>(); };
	if (auto k = j.find("separator2")  ; k != j.end()) { s.separator2   = k->get<str>(); };
	if (auto k = j.find("rseparator")  ; k != j.end()) { s.rseparator   = k->get<str>(); };
	if (auto k = j.find("rseparator2") ; k != j.end()) { s.rseparator2  = k->get<str>(); };
	if (auto k = j.find("top_prefix")  ; k != j.end()) { s.top_prefix   = k->get<str>(); };
	if (auto k = j.find("top_prefix")  ; k != j.end()) { s.top_prefix   = k->get<str>(); };
	if (auto k = j.find("bot_prefix")  ; k != j.end()) { s.bot_prefix   = k->get<str>(); };

	if (auto k = j.find("home")     ; k != j.end()) { s.home     = k->get<str>();};
	if (auto k = j.find("prompt")   ; k != j.end()) { s.prompt   = k->get<str>();};
	if (auto k = j.find("root")     ; k != j.end()) { s.root     = k->get<str>();};
	if (auto k = j.find("host")     ; k != j.end()) { s.host     = k->get<str>();};
	if (auto k = j.find("jobs")     ; k != j.end()) { s.jobs     = k->get<str>();};
	if (auto k = j.find("dir_wrap") ; k != j.end()) { s.dir_wrap = k->get<str>();};
	if (auto k = j.find("readonly") ; k != j.end()) { s.readonly = k->get<str>();};
	
	if (auto k = j.find("git_branch")  ; k != j.end()) { s.git_branch  = k->get<str>(); };
	if (auto k = j.find("git_hash")    ; k != j.end()) { s.git_hash    = k->get<str>(); };
	if (auto k = j.find("git_tag")     ; k != j.end()) { s.git_tag     = k->get<str>(); };
	if (auto k = j.find("git_stash")   ; k != j.end()) { s.git_stash   = k->get<str>(); };
	if (auto k = j.find("git_ahead")   ; k != j.end()) { s.git_ahead   = k->get<str>(); };
	if (auto k = j.find("git_behind")  ; k != j.end()) { s.git_behind  = k->get<str>(); };
	if (auto k = j.find("git_staged")  ; k != j.end()) { s.git_staged  = k->get<str>(); };
	if (auto k = j.find("git_nstaged") ; k != j.end()) { s.git_nstaged = k->get<str>(); };
	if (auto k = j.find("git_conflicted") ; k != j.end()) { s.git_conflicted = k->get<str>(); };
	if (auto k = j.find("git_untracked")  ; k != j.end()) { s.git_untracked  = k->get<str>(); };
}

void from_json(const nlohmann::json& j, module::constructor_map_t& m)
{
	Style style;
	str command;

	for (auto& [name, segment]: j.items())
	{
		auto value = segment.find("command");
		if (value == segment.end())
		{
			continue;
		}

		command = value->get<str>();
		
		value = segment.find("style"); 
		if (value != segment.end())
		{
			style = value->get<Style>();
		}


		m.emplace ( name, [=](Config c) -> Module {
			auto result = utils::exec(command);
			if (!result.empty())
			{
				return Module { {module::id::extension, result[0], style} };
			}
			return Module {};
		});
	}
}
