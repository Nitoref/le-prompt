#ifndef PROMPT_CONFIG_H
#define PROMPT_CONFIG_H

#include "module.hpp"
#include <cpptoml.hpp>
#include <memory>

#include <map>
#include <vector>



struct config
{
	enum shell_t {bash, csh, fish, ksh, zsh};

	using string = std::string;
	using strvec = std::vector<string>;


	config(int argc, char const *argv[]);

	static shell_t
	shell(string name)
	{
		std::map<string, shell_t>
    	map {
	        {"bash", shell_t::bash},
	        {"csh",  shell_t::csh},
	        {"dash", shell_t::bash},
	        {"fish", shell_t::fish},
	        {"ksh",  shell_t::ksh},
	        {"sh",   shell_t::bash},
	        {"tcsh", shell_t::csh},
	        {"zsh",  shell_t::zsh},
    	};
    	auto found = map.find(name);
    	if (found != map.end())
    		return found->second;
    	return shell_t::bash;
	}

	struct _meta
	{
		shell_t shell;
		size_t  width;
		bool    root;
		int     error;
	}
	_meta;

	struct segments
	{
		strvec left   = {"pwd", "shell"};
		strvec right  = {"time"};
		strvec down   = {};
	}
	segments;

	struct global
	{
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
	}
	global;
	
	struct user
	{
		string default_user = "";
		Style  theme        = {};
		Style  theme_root   = {};
		bool   always       = false;
	}
	user;

	struct context
	{	
		string default_user = "";
		string format;
		bool   always = false;
		Style  theme  = {};
	}
	context;

	struct dir
	{
		Style  theme_home = {};
		Style  theme_path = {};
		Style  theme_cwd  = {};
		string symbol_wrap = "…";
		string symbol_home = "~";
		bool   fancy;
		size_t depth;
		size_t length;
	}
	dir;

	struct readonly
	{
		string symbol = " ⃠";
		Style  theme;
	}
	readonly;

	struct aws
	{
		Style theme;
	}
	aws;

	struct docker
	{
		Style theme;
	}
	docker;

	struct git
	{
		string symbol_branch;
		string symbol_hash;
		string symbol_tag;
		string symbol_dirty;
		string symbol_stash;
		string symbol_ahead;
		string symbol_behind;
		string symbol_staged;
		string symbol_nstaged;
		string symbol_conflicted;
		string symbol_untracked;

		Style theme_clean;
		Style theme_dirty;
		Style theme_stash;
		Style theme_ahead;
		Style theme_behind;
		Style theme_staged;
		Style theme_nstaged;
		Style theme_untracked;
		Style theme_conflicted;

		bool   fancy;
		bool   count;
		string format = "@.><+!?x";
		strvec ignore;
	}
	git;

	struct jobs 
	{
		string symbol = "…";
		bool   count;
		bool   always;
		Style  theme;
		Style  theme_none;
	}
	jobs;

	struct root
	{
		string symbol = "#";
		Style  theme;
	}
	root;

	struct status
	{
		string symbol_success;
		string symbol_failure;
		bool   numeric;
		bool   always;
		Style  theme_success;
		Style  theme_failure;
	}
	status;

	struct virtual_env
	{
		Style theme;
	}
	virtual_env;

	struct prompt
	{
		string symbol = "$";
		Style  theme_success;
		Style  theme_failure;
	}
	prompt;

	struct time
	{
		string format = "%T";
		Style  theme;
	}
	time;

	struct ssh
	{
		Style theme;
	}
	ssh;


private:

	using table_ptr = std::shared_ptr<cpptoml::table>;

	void parse(string filename);

	template<class T>
	void get(const table_ptr data, string key, T& t);
	void get(const table_ptr data, string key, Style& style);
	// template<class T>
	void get(const table_ptr data, string key, std::vector<string>& t);

	void get_segments   (table_ptr table);
	void get_global     (table_ptr table);
	void get_user       (table_ptr table);
	void get_context    (table_ptr table);
	void get_dir        (table_ptr table);
	void get_readonly   (table_ptr table);
	void get_aws        (table_ptr table);
	void get_docker     (table_ptr table);
	void get_git        (table_ptr table);
	void get_jobs       (table_ptr table);
	void get_root       (table_ptr table);
	void get_status     (table_ptr table);
	void get_virtual_env(table_ptr table);
	void get_prompt     (table_ptr table);
	void get_time       (table_ptr table);
	void get_ssh        (table_ptr table);
};


#endif