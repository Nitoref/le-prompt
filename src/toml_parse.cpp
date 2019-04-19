#include "toml_parse.hpp"
#include "config.hpp"

#include <memory>
#include <vector>


namespace toml
{

void parse(config& config, std::string filename)
{
    auto file = cpptoml::parse_file(filename);
    if (!file)
        return;
    if (auto t = file -> get_table("segments"))  { get_segments    (t, config); } ;
    if (auto t = file -> get_table("global"))    { get_global      (t, config); } ;
    if (auto t = file -> get_table("user"))      { get_user        (t, config); } ;
    if (auto t = file -> get_table("context"))   { get_context     (t, config); } ;
    if (auto t = file -> get_table("dir") )      { get_dir         (t, config); } ;
    if (auto t = file -> get_table("readonly"))  { get_readonly    (t, config); } ;
    if (auto t = file -> get_table("aws") )      { get_aws         (t, config); } ;
    if (auto t = file -> get_table("docker"))    { get_docker      (t, config); } ;
    if (auto t = file -> get_table("git") )      { get_git         (t, config); } ;
    if (auto t = file -> get_table("jobs"))      { get_jobs        (t, config); } ;
    if (auto t = file -> get_table("root"))      { get_root        (t, config); } ;
    if (auto t = file -> get_table("status"))    { get_status      (t, config); } ;
    if (auto t = file -> get_table("virtualenv")){ get_virtual_env (t, config); } ;
    if (auto t = file -> get_table("prompt"))    { get_prompt      (t, config); } ;
    if (auto t = file -> get_table("time"))      { get_time        (t, config); } ;
    if (auto t = file -> get_table("ssh") )      { get_ssh         (t, config); } ;
};

void get_segments(table_ptr table, config& c)
{
    get(table, "left",  c.segments.left);
    get(table, "right", c.segments.right);
    get(table, "down",  c.segments.down);
}

void get_global(table_ptr table, config& c)
{
    get(table, "padding_left"  , c.global.padding_left);
    get(table, "padding_right" , c.global.padding_right);
    get(table, "padding_end"   , c.global.padding_end);
    get(table, "separator"     , c.global.separator);
    get(table, "separator2"    , c.global.separator2);
    get(table, "separator"     , c.global.separator);
    get(table, "separator2"    , c.global.separator2);
    get(table, "top_prefix"    , c.global.top_prefix);
    get(table, "bot_prefix"    , c.global.bot_prefix);
    get(table, "force_newline" , c.global.force_newline);
    get(table, "native_rprompt", c.global.native_rprompt);
}

void get_user(table_ptr table, config& c)
{
    get(table, "default_user" , c.user.default_user);
    get(table, "theme"        , c.user.theme);
    get(table, "theme.root"   , c.user.theme_root);
    get(table, "always"       , c.user.always);
}

void get_context(table_ptr table, config& c)
{   
    get(table, "default_user", c.context.default_user);
    get(table, "template"    , c.context.format);
    get(table, "always"      , c.context.always);
    get(table, "theme"       , c.context.theme);
}

void get_dir(table_ptr table, config& c)
{
    get(table, "theme.home" , c.dir.theme_home);
    get(table, "theme.path" , c.dir.theme_path);
    get(table, "theme.cwd"  , c.dir.theme_cwd);
    get(table, "symbol.wrap", c.dir.symbol_wrap);
    get(table, "symbol.home", c.dir.symbol_home);
    get(table, "fancy"      , c.dir.fancy);
    get(table, "depth"      , c.dir.depth);
    get(table, "length"     , c.dir.length);
}

void get_readonly(table_ptr table, config& c)
{
    get(table, "theme" , c.readonly.theme);
    get(table, "symbol", c.readonly.symbol);
}

void get_aws(table_ptr table, config& c)
{
    get(table, "theme", c.aws.theme);
}

void get_docker(table_ptr table, config& c)
{
    get(table, "theme", c.docker.theme);
}

void get_git(table_ptr table, config& c)
{
    get(table, "symbol.branch"    , c.git.symbol_branch);
    get(table, "symbol.hash"      , c.git.symbol_hash);
    get(table, "symbol.tag"       , c.git.symbol_tag);
    get(table, "symbol.stash"     , c.git.symbol_stash);
    get(table, "symbol.ahead"     , c.git.symbol_ahead);
    get(table, "symbol.behind"    , c.git.symbol_behind);
    get(table, "symbol.staged"    , c.git.symbol_staged);
    get(table, "symbol.nstaged"   , c.git.symbol_nstaged);
    get(table, "symbol.conflicted", c.git.symbol_conflicted);
    get(table, "symbol.untracked" , c.git.symbol_untracked);

    get(table, "theme.clean"     , c.git.theme_clean);
    get(table, "theme.dirty"     , c.git.theme_dirty);
    get(table, "theme.stash"     , c.git.theme_stash);
    get(table, "theme.ahead"     , c.git.theme_ahead);
    get(table, "theme.behind"    , c.git.theme_behind);
    get(table, "theme.staged"    , c.git.theme_staged);
    get(table, "theme.nstaged"   , c.git.theme_nstaged);
    get(table, "theme.untracked" , c.git.theme_untracked);
    get(table, "theme.conflicted", c.git.theme_conflicted);

    get(table, "fancy"   , c.git.fancy);
    get(table, "count"   , c.git.count);
    get(table, "template", c.git.format);
    get(table, "ignore"  , c.git.ignore);
}

void get_jobs(table_ptr table, config& c)
{
    get(table, "symbol"       , c.jobs.symbol);
    get(table, "count"        , c.jobs.count);
    get(table, "always"       , c.jobs.always);
    get(table, "theme"        , c.jobs.theme);
    get(table, "theme.none"   , c.jobs.theme_none);
}

void get_root(table_ptr table, config& c)
{
    get(table, "symbol", c.root.symbol);
    get(table, "theme" , c.root.theme);
}

void get_status(table_ptr table, config& c)
{
    get(table, "symbol.success", c.status.symbol_success);
    get(table, "symbol.failure", c.status.symbol_failure);
    get(table, "numeric"       , c.status.numeric);
    get(table, "theme.success" , c.status.theme_success);
    get(table, "theme.failure" , c.status.theme_failure);
}

void get_virtual_env(table_ptr table, config& c)
{
    get(table, "theme", c.virtual_env.theme);
}

void get_prompt(table_ptr table, config& c)
{
    get(table, "symbol"       , c.prompt.symbol);
    get(table, "theme.success", c.prompt.theme_success);
    get(table, "theme.failure", c.prompt.theme_failure);
}

void get_time(table_ptr table, config& c)
{
    get(table, "template", c.time.format);
    get(table, "theme"   , c.time.theme);
}

void get_ssh(table_ptr table, config& c)
{
    get(table, "theme", c.ssh.theme);
}

template<class T>
void get(const table_ptr data, string key, T& t)
{
    auto value = data -> get_qualified_as<T>(key);
    if (value)
        t = *value; 
}

void get(const table_ptr data, string key, Style& style)
{
    auto table = data -> get_table_qualified(key);
    if (!table)
        return;

    auto fg = table -> get_as<int>("fg");
    if (fg) style.fg = *fg;
    auto bg = table -> get_as<int>("bg");
    if (bg) style.bg = *bg;
}

// template<class T>
void get(const table_ptr data, string key, std::vector<string>& t)
{
    auto values = data -> get_array_of<string>(key);
    if (!values)
        return;
    t.clear();
    t.reserve(values->size());
    for (const auto& value: *values)
        t.push_back(value);
}


}
