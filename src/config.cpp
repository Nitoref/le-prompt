#include "config.hpp"
#include "utils.hpp"

#include <unistd.h>
#include <vector>
#include <iostream>


config::config(int argc, char const *argv[])
{
	assert(argc >= 2 && "Thou shall provide shell name "
						"and $? ($status for fish)"
						"as first arguments.\n");

    _meta.shell = config::shell(argv[1]);
    _meta.error = std::stoi(argv[2]);
    _meta.width = utils::term_width();
    _meta.root  = getuid() == 0;

    if (argc > 3) try
    {
        parse(argv[3]);
    }
    catch (...) {
        std::cout << "<!config>" << "\n";
    }
}

void config::parse(std::string filename)
{
    auto file = cpptoml::parse_file(filename);
    if (!file)
        return;
    if (auto t = file -> get_table("segments"))  { get_segments    (t); } ;
    if (auto t = file -> get_table("global"))    { get_global      (t); } ;
    if (auto t = file -> get_table("user"))      { get_user        (t); } ;
    if (auto t = file -> get_table("host"))      { get_host        (t); } ;
    if (auto t = file -> get_table("context"))   { get_context     (t); } ;
    if (auto t = file -> get_table("dir") )      { get_dir         (t); } ;
    if (auto t = file -> get_table("perms"))     { get_perms       (t); } ;
    if (auto t = file -> get_table("aws") )      { get_aws         (t); } ;
    if (auto t = file -> get_table("docker"))    { get_docker      (t); } ;
    if (auto t = file -> get_table("git") )      { get_git         (t); } ;
    if (auto t = file -> get_table("jobs"))      { get_jobs        (t); } ;
    if (auto t = file -> get_table("root"))      { get_root        (t); } ;
    if (auto t = file -> get_table("status"))    { get_status      (t); } ;
    if (auto t = file -> get_table("virtualenv")){ get_virtual_env (t); } ;
    if (auto t = file -> get_table("prompt"))    { get_prompt      (t); } ;
    if (auto t = file -> get_table("time"))      { get_time        (t); } ;
    if (auto t = file -> get_table("ssh") )      { get_ssh         (t); } ;
};

void config::get_segments(table_ptr table)
{
    get(table, "left",  segments.left);
    get(table, "right", segments.right);
    get(table, "down",  segments.down);
}

void config::get_global(table_ptr table)
{
    get(table, "width_limit"   , global.width_limit);
    get(table, "padding_left"  , global.padding_left);
    get(table, "padding_right" , global.padding_right);
    get(table, "padding_end"   , global.padding_end);
    get(table, "force_newline" , global.force_newline);
    get(table, "native_rprompt", global.native_rprompt);
    get(table, "symbol.separator"   , global.separator);
    get(table, "symbol.separator2"  , global.separator2);
    get(table, "symbol.rseparator"  , global.rseparator);
    get(table, "symbol.rseparator2" , global.rseparator2);
    get(table, "symbol.top_prefix"  , global.top_prefix);
    get(table, "symbol.bot_prefix"  , global.bot_prefix);
}

void config::get_user(table_ptr table)
{
    get(table, "default_user" , user.default_user);
    get(table, "symbol"       , user.symbol);
    get(table, "theme"        , user.theme);
    get(table, "theme.root"   , user.theme_root);
    get(table, "always"       , user.always);
}

void config::get_host(table_ptr table)
{
    get(table, "short" , host.shorten);
    get(table, "symbol", host.symbol);
    get(table, "theme" , host.theme);
}

void config::get_context(table_ptr table)
{   
    get(table, "template"    , context.format);
    get(table, "theme"       , context.theme);
    get(table, "theme.root"  , context.theme_root);
}

void config::get_dir(table_ptr table)
{
    get(table, "theme.home" , dir.theme_home);
    get(table, "theme.path" , dir.theme_path);
    get(table, "theme.cwd"  , dir.theme_cwd);
    get(table, "symbol.wrap", dir.symbol_wrap);
    get(table, "symbol.home", dir.symbol_home);
    get(table, "fancy"      , dir.fancy);
    get(table, "depth"      , dir.depth);
    get(table, "length"     , dir.length);
    get(table, "alias"      , dir.alias);
}

void config::get_perms(table_ptr table)
{
    get(table, "verbose", perms.verbose);
    get(table, "theme"  , perms.theme);
    get(table, "symbol.readonly", perms.symbol_readonly);
    get(table, "theme.readonly" , perms.theme_readonly);
}

void config::get_aws(table_ptr table)
{
    get(table, "theme", aws.theme);
}

void config::get_docker(table_ptr table)
{
    get(table, "theme", docker.theme);
}

void config::get_git(table_ptr table)
{
    get(table, "symbol.branch"    , git.symbol_branch);
    get(table, "symbol.hash"      , git.symbol_hash);
    get(table, "symbol.tag"       , git.symbol_tag);
    get(table, "symbol.stash"     , git.symbol_stash);
    get(table, "symbol.ahead"     , git.symbol_ahead);
    get(table, "symbol.behind"    , git.symbol_behind);
    get(table, "symbol.staged"    , git.symbol_staged);
    get(table, "symbol.nstaged"   , git.symbol_nstaged);
    get(table, "symbol.conflicted", git.symbol_conflicted);
    get(table, "symbol.untracked" , git.symbol_untracked);

    get(table, "theme.clean"     , git.theme_clean);
    get(table, "theme.dirty"     , git.theme_dirty);
    get(table, "theme.stash"     , git.theme_stash);
    get(table, "theme.ahead"     , git.theme_ahead);
    get(table, "theme.behind"    , git.theme_behind);
    get(table, "theme.staged"    , git.theme_staged);
    get(table, "theme.nstaged"   , git.theme_nstaged);
    get(table, "theme.untracked" , git.theme_untracked);
    get(table, "theme.conflicted", git.theme_conflicted);
    get(table, "theme.ignored"   , git.theme_ignored);

    get(table, "fancy"   , git.fancy);
    get(table, "count"   , git.count);
    get(table, "template", git.format);
    get(table, "ignore"  , git.ignore);
}

void config::get_jobs(table_ptr table)
{
    get(table, "symbol"       , jobs.symbol);
    get(table, "count"        , jobs.count);
    get(table, "always"       , jobs.always);
    get(table, "theme"        , jobs.theme);
    get(table, "theme.none"   , jobs.theme_none);
}

void config::get_root(table_ptr table)
{
    get(table, "symbol", root.symbol);
    get(table, "theme" , root.theme);
}

void config::get_status(table_ptr table)
{
    get(table, "symbol.success", status.symbol_success);
    get(table, "symbol.failure", status.symbol_failure);
    get(table, "numeric"       , status.numeric);
    get(table, "theme.success" , status.theme_success);
    get(table, "theme.failure" , status.theme_failure);
}

void config::get_virtual_env(table_ptr table)
{
    get(table, "theme", virtual_env.theme);
}

void config::get_prompt(table_ptr table)
{
    get(table, "symbol"       , prompt.symbol);
    get(table, "theme.success", prompt.theme_success);
    get(table, "theme.failure", prompt.theme_failure);
}

void config::get_time(table_ptr table)
{
    get(table, "template", time.format);
    get(table, "theme"   , time.theme);
}

void config::get_ssh(table_ptr table)
{
    get(table, "theme", ssh.theme);
}


template<class T>
void config::get(const table_ptr data, string key, T& t)
{
    auto value = data -> get_qualified_as<T>(key);
    if (value)
        t = *value; 
}

void config::get(const table_ptr data, string key, Style& s)
{
    auto table = data -> get_table_qualified(key);
    if (!table)
        return;

    auto fg = table -> get_as<int>("fg");
    if (fg) s.fg = *fg;
    auto bg = table -> get_as<int>("bg");
    if (bg) s.bg = *bg;
}

void config::get(const table_ptr data, string key, strvec& t)
{
    auto values = data -> get_array_of<string>(key);
    if (!values)
        return;
    t.clear(), t.reserve(values->size());
    for (const auto& value: *values)
        t.push_back(value);
}

void config::get(const table_ptr data, string key, strmap& t)
{
    auto values = data -> get_table_array(key);
    if (!values)
        return;
    for (const auto& value: *values)    // for each table_array
    	for (const auto& pair: *value)  // for each pair
            if (const auto& v = pair.second->as<string>())
                t.emplace(pair.first, v->get());
}
