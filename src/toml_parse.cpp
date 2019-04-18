#include "toml_parse.hpp"


namespace toml
{
using string = std::string;


void parse(Config& config, string filename) {
	
    auto file = cpptoml::parse_file(filename);
	
    if (auto a = file -> get_table("segments"))
    {
	    get_segments(a, config.args);
    }
    if (auto a = file -> get_table("args"))
    {
      get_arguments(a, config.args);
    }
	if (auto s = file -> get_table("symbols"))
    {
	    get_symbols(s, config.symbols);
    }
	if (auto t = file -> get_table("theme"))
    {
	    get_theme(t, config.theme);
    }
    if (auto e = file -> get_table_array("extensions"))
    {
        get_extensions(e);
    }
}

void get_extensions(std::shared_ptr<cpptoml::table_array> extensions)
{
    for (const auto& extension : *extensions)
    {
        string name;
        string command;
        Style style;
        if (auto s = extension->get_as<string>("name")) {name = *s;};
        if (auto s = extension->get_as<string>("command")) {command = *s;};
        if (auto s = extension->get_table("style")) {get_style (s, style);};
        if (!name.empty() && !command.empty())
        {
            
        }
    }    
}


void get_segments(std::shared_ptr<cpptoml::table> args, Arguments& a)
{
    if ( auto v = args -> get_array_of<string> ("left") ) {a.left_segments  = *v;};
    if ( auto v = args -> get_array_of<string> ("right")) {a.right_segments = *v;};
    if ( auto v = args -> get_array_of<string> ("down") ) {a.down_segments  = *v;};
}

void get_arguments(std::shared_ptr<cpptoml::table> args, Arguments& a)
{
    cpptoml::option<int> i;
    cpptoml::option<bool> b;
    cpptoml::option<string> s;

    if ((i = args -> get_as<int>    ("timeout")       )) { a.timeout        = *i;};
    if ((i = args -> get_as<int>    ("width_limit")   )) { a.width_limit    = *i;};
    if ((i = args -> get_as<int>    ("padding_left")  )) { a.padding_left   = *i;};
    if ((i = args -> get_as<int>    ("padding_right") )) { a.padding_right  = *i;};
    if ((i = args -> get_as<int>    ("padding_end")   )) { a.padding_end    = *i;};
    if ((b = args -> get_as<bool>   ("force_newline") )) { a.force_newline  = *b;};
    if ((b = args -> get_as<bool>   ("native_rprompt"))) { a.native_rprompt = *b;};

    if ((b = args -> get_as<bool>   ("numeric_status"))) { a.numeric_status  = *b;};
    if ((b = args -> get_as<bool>   ("jobs_count")    )) { a.jobs_count    = *b;};

    if ((s = args -> get_as<string> ("default_user") )) { a.default_user = *s;};
    if ((s = args -> get_as<string> ("default_host") )) { a.default_host = *s;};
    if ((s = args -> get_as<string> ("time_format")  )) { a.time_format  = *s;};

    if ((i = args -> get_as<int>    ("dir_depth")  )) { a.dir_depth  = *i;};
    if ((i = args -> get_as<int>    ("dir_length") )) { a.dir_length = *i;};
    if ((b = args -> get_as<bool>   ("dir_fancy")  )) { a.dir_fancy  = *b;};

    if ((s = args -> get_as<string> ("git_format") )) { a.git_format  = *s;};
    if ((b = args -> get_as<bool>   ("git_fancy")  )) { a.git_fancy = *b;};
    if ((b = args -> get_as<bool>   ("git_count")  )) { a.git_count   = *b;};
    if ( auto v = args -> get_array_of<string> ("git_ignore")) {a.git_ignore  = *v;};
};




void get_style(std::shared_ptr<cpptoml::table> k, Style& s)
{
    if (auto i = k->get_as<int>("fg")) {s.fg = *i;}
    if (auto i = k->get_as<int>("bg")) {s.bg = *i;}
}

void get_theme(std::shared_ptr<cpptoml::table> theme, Theme& t)
{
    std::shared_ptr<cpptoml::table> k;

    if (( k = theme -> get_table("separator") )) { get_style (k, t.separator);};

    if (( k = theme -> get_table("username") )) { get_style (k, t.username);};
    if (( k = theme -> get_table("root")     )) { get_style (k, t.root);};
    if (( k = theme -> get_table("hostname") )) { get_style (k, t.hostname);};

    if (( k = theme -> get_table("home")     )) { get_style (k, t.home);};
    if (( k = theme -> get_table("path")     )) { get_style (k, t.path);};
    if (( k = theme -> get_table("dir")      )) { get_style (k, t.dir);};
    if (( k = theme -> get_table("readonly") )) { get_style (k, t.readonly);};

    if (( k = theme -> get_table("time")        )) { get_style (k, t.time);};
    if (( k = theme -> get_table("jobs")        )) { get_style (k, t.jobs);};
    if (( k = theme -> get_table("ssh")         )) { get_style (k, t.ssh);};
    if (( k = theme -> get_table("aws")         )) { get_style (k, t.aws);};
    if (( k = theme -> get_table("docker")      )) { get_style (k, t.docker);};
    if (( k = theme -> get_table("dot_env")     )) { get_style (k, t.dot_env);};
    if (( k = theme -> get_table("virtual_env") )) { get_style (k, t.virtual_env);};
    if (( k = theme -> get_table("duration")    )) { get_style (k, t.duration);};

    if (( k = theme -> get_table("git_clean")      )) { get_style (k, t.git_clean);};
    if (( k = theme -> get_table("git_stash")      )) { get_style (k, t.git_stash);};
    if (( k = theme -> get_table("git_dirty")      )) { get_style (k, t.git_dirty);};
    if (( k = theme -> get_table("git_ahead")      )) { get_style (k, t.git_ahead);};
    if (( k = theme -> get_table("git_behind")     )) { get_style (k, t.git_behind);};
    if (( k = theme -> get_table("git_staged")     )) { get_style (k, t.git_staged);};
    if (( k = theme -> get_table("git_nstaged")    )) { get_style (k, t.git_nstaged);};
    if (( k = theme -> get_table("git_untracked")  )) { get_style (k, t.git_untracked);};
    if (( k = theme -> get_table("git_conflicted") )) { get_style (k, t.git_conflicted);};

    if (( k = theme -> get_table("exit_success")   )) { get_style (k, t.exit_success);};
    if (( k = theme -> get_table("exit_failure")   )) { get_style (k, t.exit_failure);};
}


void get_symbols(std::shared_ptr<cpptoml::table> symbols, Symbols& s)
{
    cpptoml::option<string> o;

    if (( o = symbols -> get_as<string>("separator")   )) { s.separator = *o;};
    if (( o = symbols -> get_as<string>("separator2")  )) { s.separator2 = *o;};
    if (( o = symbols -> get_as<string>("rseparator")  )) { s.rseparator = *o;};
    if (( o = symbols -> get_as<string>("rseparator2") )) { s.rseparator2 = *o;};
    if (( o = symbols -> get_as<string>("top_prefix")  )) { s.top_prefix = *o;};
    if (( o = symbols -> get_as<string>("top_prefix")  )) { s.top_prefix = *o;};
    if (( o = symbols -> get_as<string>("bot_prefix")  )) { s.bot_prefix = *o;};

    if (( o = symbols -> get_as<string>("home")     )) { s.home = *o;};
    if (( o = symbols -> get_as<string>("prompt")   )) { s.prompt = *o;};
    if (( o = symbols -> get_as<string>("root")     )) { s.root = *o;};
    if (( o = symbols -> get_as<string>("host")     )) { s.host = *o;};
    if (( o = symbols -> get_as<string>("jobs")     )) { s.jobs = *o;};
    if (( o = symbols -> get_as<string>("dir_wrap") )) { s.dir_wrap = *o;};
    if (( o = symbols -> get_as<string>("readonly") )) { s.readonly = *o;};

    if (( o = symbols -> get_as<string>("git_branch")     )) { s.git_branch = *o;};
    if (( o = symbols -> get_as<string>("git_hash")       )) { s.git_hash = *o;};
    if (( o = symbols -> get_as<string>("git_tag")        )) { s.git_tag = *o;};
    if (( o = symbols -> get_as<string>("git_stash")      )) { s.git_stash = *o;};
    if (( o = symbols -> get_as<string>("git_ahead")      )) { s.git_ahead = *o;};
    if (( o = symbols -> get_as<string>("git_behind")     )) { s.git_behind = *o;};
    if (( o = symbols -> get_as<string>("git_staged")     )) { s.git_staged = *o;};
    if (( o = symbols -> get_as<string>("git_nstaged")    )) { s.git_nstaged = *o;};
    if (( o = symbols -> get_as<string>("git_conflicted") )) { s.git_conflicted = *o;};
    if (( o = symbols -> get_as<string>("git_untracked")  )) { s.git_untracked = *o;};
};


}
