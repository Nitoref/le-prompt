#ifndef PROMPT_CONFIG_H
#define PROMPT_CONFIG_H

#include "shell.hpp"
#include "theme.hpp"
#include <cpptoml.h>

#include <map>
#include <vector>
#include <memory>
#include <filesystem>



namespace fs = std::filesystem;


struct config
{

	using string = std::string;
	using strvec = std::vector<string>;
	using strmap = std::map<string, string>;
	
	using parse_exception = cpptoml::parse_exception;


	config(int argc, char const *argv[]);


	struct _meta
	{
		fs::path cwd;
		shell_t  shell;
		size_t   width;
		bool     root;
		int      error;
	}
	_meta;

	struct segments
	{
		strvec left   = {"context", "pwd", "shell"};
		strvec right  = {"time", "git", "status", "jobs", "root"};
		strvec down   = {};
	}
	segments;

	struct global
	{
		double width_limit   = 0.7;
		size_t padding_left  = 1;
		size_t padding_right = 1;
		size_t padding_end   = 0;
		string separator   = "\uE0B0";
		string separator2  = "\uE0B1";
		string rseparator  = "\uE0B2";
		string rseparator2 = "\uE0B3";
		string top_prefix  = "";
		string bot_prefix  = "";
		bool   force_newline  = false;
		bool   native_rprompt = false;
		int    timeout = 100;
		Theme  theme_background;
		Theme  theme_separator;
	}
	global;
	
	struct user
	{
		bool   always = false;
		string ignore = "";
		string symbol = "";
		Theme  theme      = {};
		Theme  theme_root = {};
	}
	user;

	struct host
	{
		bool   shorten = true;
		string symbol  = "";
		Theme  theme;
	}
	host;

	struct context
	{	
		string format = "u@h";
		Theme  theme  = {};
		Theme  theme_root = {};
	}
	context;

	struct dir
	{
		bool   fancy  = false;
		size_t depth  = 5;
		size_t length = 0;
		strmap alias  = {};
		Theme  theme_home  = {};
		Theme  theme_path  = {};
		Theme  theme_cwd   = {};
		string symbol_wrap = "…";
		string symbol_home = "~";
	}
	dir;

	struct perms
	{
		bool   verbose = false;
		string symbol_readonly = " ⃠";
		Theme  theme_readonly  = {};
		Theme  theme = {};
	}
	perms;

	struct aws
	{
		bool   always;
		string ignore;
		string symbol;
		Theme theme;
	}
	aws;

	struct docker
	{
		string symbol;
		Theme  theme;
	}
	docker;

	struct hg
	{
		string symbol_branch;
		string symbol_hash;
		Theme  theme;
	}
	hg;

	struct git
	{
		bool   count  = false;
		bool   hash_fallback = true;
		string format = "@%.><+!?x";
		strvec ignore = {};

		string symbol_branch;
		string symbol_hash  = "#";
		string symbol_tag   = "&";
		string symbol_dirty = "✳";
		string symbol_stash = "°";
		string symbol_ahead   = "↑";
		string symbol_behind  = "↓"; 
		string symbol_staged  = "+";
		string symbol_notstaged  = "!"; 
		string symbol_conflicted = "×";
		string symbol_untracked  = "?";

		Theme theme_clean;
		Theme theme_dirty;
		Theme theme_tag;
		Theme theme_stash;
		Theme theme_ahead;
		Theme theme_behind;
		Theme theme_staged;
		Theme theme_notstaged;
		Theme theme_untracked;
		Theme theme_conflicted;
		Theme theme_ignored;
	}
	git;

	struct jobs 
	{
		bool   count  = false;
		bool   always = false;
		string symbol = "…";
		Theme  theme;
		Theme  theme_none;
	}
	jobs;

	struct root
	{
		string symbol = "#";
		Theme  theme;
	}
	root;

	struct status
	{
		bool   numeric = false;
		bool   always  = false;
		string symbol_success = "";
		string symbol_failure = "";
		Theme  theme_success;
		Theme  theme_failure;
	}
	status;

	struct venv
	{
		bool   verbose = true;
		string symbol;
		Theme  theme;
	}
	venv;

	struct shell
	{
		string symbol_all  = "$";
		string symbol_bash = "$";
		string symbol_csh  = "%";
		string symbol_zsh  = "%";
		string symbol_ksh  = "$";
		string symbol_fish = ">";
		string symbol_ps   = ">";
		Theme  theme_success;
		Theme  theme_failure;
	}
	shell;

	struct time
	{
		string format = "%T";
		Theme  theme;
	}
	time;

	struct ssh
	{
		bool   verbose = true;
		string symbol;
		Theme  theme;
	}
	ssh;


	struct load
	{
		string symbol;
		Theme  theme;
	}
	load;


	using table_ptr = std::shared_ptr<cpptoml::table>;

	void parse(string filename);

	template<class T>
	void get(const table_ptr data, string key, T& t);
	void get(const table_ptr data, string key, Theme& s);
	void get(const table_ptr data, string key, strvec& t);
	void get(const table_ptr data, string key, strmap& t);

	void get_segments   (table_ptr table);
	void get_global     (table_ptr table);
	void get_user       (table_ptr table);
	void get_host       (table_ptr table);
	void get_context    (table_ptr table);
	void get_dir        (table_ptr table);
	void get_perms      (table_ptr table);
	void get_aws        (table_ptr table);
	void get_docker     (table_ptr table);
	void get_hg         (table_ptr table);
	void get_git        (table_ptr table);
	void get_jobs       (table_ptr table);
	void get_root       (table_ptr table);
	void get_status     (table_ptr table);
	void get_venv       (table_ptr table);
	void get_shell      (table_ptr table);
	void get_time       (table_ptr table);
	void get_ssh        (table_ptr table);
	void get_load       (table_ptr table);
};


#endif