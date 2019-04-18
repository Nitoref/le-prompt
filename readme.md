A fully featured theme for your shell with left, right and multi-line prompt support for bash, ksh, tcsh, zsh and fish.

This theme is for people that love their good ol' shell, or don't want/can switch to zsh - but still want a wonderfull looking shell like all the cool kids. It's also a theme for people that have to work in different environements, but want a unifying experience.

* Fast.
* Shell agnostic right and multi-line prompt support.
* Easily configurable.
* Extensible.

#### Yet another one ?

[powerline-go](https://github.com/justjanne/powerline-go) is the closest project from this one, and has heavily influenced it - this project adresses some of its drawbacks by providing better performance (written in C++ with libgit2 integration and parallelization), shell support, right prompt support and a better configuration format.

#### Installation

#####Requisites

 `xterm-256color`compatible terminal as well as [powerline fonts](https://github.com/powerline/fonts)  /  [nerd fonts](https://github.com/ryanoasis/nerd-fonts) are highly recommended to fully enjoy this software.

###### bash 

```bash
# file: .bash_profile

POWERLINE_EXE="/path/to/powerline"
POWERLINE_CONFIG="/path/to/config.json"
function update_prompt() {
 	PS1="$($POWERLINE_EXE bash $? $POWERLINE_CONFIG)"
}
PROMPT_COMMAND="update_prompt; $PROMPT_COMMAND"
```

###### zsh 

```sh
#file: .zprofile

POWERLINE_EXE="/path/to/powerline"
POWERLINE_CONFIG="/path/to/config.json"

function update_prompt() {
	TMP=("${(f)$($POWERLINE_EXE zsh $? $POWERLINE_CONFIG)}")
	PS1="$TMP[1] "; RPROMPT="$TMP[2]"
}
precmd_functions+=(update_prompt)
```

###### (t)csh 

```sh
# file: .(t)cshrc

set POWERLINE_EXE     = "path/to/powerline"
set POWERLINE_CONFIG  = "path/to/config.json"
set POWERLINE_COMMAND = '$POWERLINE_EXE $0 $? $POWERLINE_CONFIG'
alias precmd 'set prompt="`$POWERLINE_EXE csh $? $POWERLINE_CONFIG`"'

```

###### fish 

```sh
# file: config.fish

set -U POWERLINE_EXE "path/to/powerline"
set -U POWERLINE_CONFIG "path/to/config.json"

function fish_prompt
    set -U PROMPT ($POWERLINE_EXE fish $status $POWERLINE_CONFIG)
    printf $PROMPT[1]
end
function fish_right_prompt
    printf $PROMPT[2]
end
```



### Configuration

The configuration file is a TOML document (yay) with five sections:

```toml
[segments]
...
[args]
...
[symbols]
...
[theme]
...
[[extensions]]
...
```



`[segments]` list the modules to draw in your prompt.

```toml
[segments]

left   = ['perms','dir']
right  = ['time','host','root','jobs','git','status']
bottom = ['shell']
```

Special requirements, or a feature not implemented yet ? Just turn any command into a module on your prompt.  If a module is already named that way, it'll get overriden. You may or may not want to call this very program from an extension. 

```javascript
[[extensions]]
name    = "size"
command = "du -sh | head -c 5"
style   = {"bg":155, "fg": 210}

[[extensions]]
name = "version"
command = 
```



`[args]` holds informations on which modules you want to display and their respective options. 

```toml
[args]

# Left aligned, right aligned and newline modules
left_segments = ["user","perms","pwd","root","exit"]
right_segments = ["time","host","git","jobs"]
down_segments = []

# [0 - 1] , maximum prompt / input ratio allowed
width_limit = 1

# Margins between each segment, and cursor offset
padding_left =   = 1
padding_right =  = 1
padding_end =    = 1

# Force a newline character after prompt even without down modules
force_newline  = false
native_rprompt = false

# Show last exit status as integer instead of string interpretation
numeric_status = false

# Show the number of background jobs
jobs_count = true

# Disable user module under that condition
default_user = ""

# Disable host module under that condition
default_host = ""

# Time module format
time_format = "%H:%M:%S"

# Amount of parent directories allowed in dir module before truncation
dir_depth = 4
# Maximum length of each directory before truncation
dir_length = 0
# Split path in different segments
dir_fancy = : false
# Aliases to shorten dir module
path_aliases = [
	{"/usr/local/bin" = "bin"},
]

# Structure of git module :
# @ -> branch name or hash
# . -> stash
# > -> ahead
# < -> behind
# + -> staged
# ! -> not staged
# ? -> untracked
# x -> conflicted
git_format =  "@.><+!?x"
# Display informations in different segments
git_fancy = true
# Display amount of files for each segment
git_count  =  true
# Absolute paths to ignored git working directories
git_ignore =  {}

```



`[symbols]` 

You have control over every symbol used by the modules.

```toml
separator   = "\uE0B0"
separator2  = "\uE0B1"
rseparator  = "\uE0B2"
rseparator2 = "\uE0B3"

top_prefix = ""
bot_prefix = ""

home     = "~"
prompt   = ">"
root     = "#"
host     = "@"
jobs     = "…"
readonly = " ⃠"
dir_wrap = "…"

git_branch   = ""
git_dirty    = "✳"
git_hash     = "#"
git_tag      = "&"
git_stash    = "*"
git_ahead    = "↑"
git_behind   = "↓"
git_staged   = "+"
git_nstaged  = "!"
git_conflicted = "×"
git_untracked  = "?"

```

