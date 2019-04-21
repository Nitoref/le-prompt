A no-latency fully featured theme with left, right and multi-line prompt support for bash, zsh, fish, ksh, tcsh.

No subprocess, no pipes to grep and perl, no hidden python interpreter, it's just plain C++.

#### Yet another one ?

This theme is for people that love their good ol' shell, or don't want/can switch to zsh - but still want a wonderfull looking shell like all the cool kids. It's also a theme for people that have to work in different environements, but want a unifying experience.

[powerline-go](https://github.com/justjanne/powerline-go) is the closest project from this one, and has heavily influenced it - this project adresses some of its drawbacks by providing better performance (written in C++ with parallelization and libgit2 integration), wider shell support, right prompt support for every shell, extensibility and a better configuration format.

If youre coming from something like powerlevel9k, this theme offers a proper configuration file format and a shrinking system: instead of simply removing the right prompt when short in space, the least prioritized segments are removed from both ends until an acceptable length is reached. Also performance.

#### It is overkill, right?

Absolutely

#### How do I get it ?

#####Requisites

 `xterm-256color`compatible terminal as well as [powerline fonts](https://github.com/powerline/fonts)  /  [nerd fonts](https://github.com/ryanoasis/nerd-fonts) are highly recommended to fully enjoy this software.



```bash
# file: .bashrc

LE_PROMPT_EXE="/Users/nitoref/le_prompt/build/bin/powerline"
LE_PROMPT_CONFIG="/Users/nitoref/le_prompt/src/presets/pure.toml"

function le_prompt() {
 	PS1="$($LE_PROMPT_EXE bash $? $LE_PROMPT_CONFIG)"
}
PROMPT_COMMAND="le_prompt; $PROMPT_COMMAND"
```

```sh
#file: .zshrc

LE_PROMPT_EXE="/Users/nitoref/Desktop/powerless/C++/build/bin/powerline"
LE_PROMPT_CONFIG="/Users/nitoref/Desktop/powerless/C++/src/presets/pure.toml"

function le_prompt() {
	LE_ERROR=$?
	TMP=("${(f)$($LE_PROMPT_EXE zsh $LE_ERROR $LE_PROMPT_CONFIG)}")
	[ -n "$TMP[1]" ] && print -P $TMP[1]; PS1=$TMP[2]; RPS1=$TMP[3]
}
precmd_functions+=(le_prompt)
```

```sh
# file: .(t)cshrc

set LE_PROMPT_EXE     = "/Users/nitoref/Desktop/powerless/C++/build/bin/powerline"
set LE_PROMPT_CONFIG  = "/Users/nitoref/Desktop/powerless/C++/src/presets/minimal.toml"
alias precmd 'set prompt="`$LE_PROMPT_EXE csh $? $LE_PROMPT_CONFIG`"'
```

```sh
# file: .config.fish
set -U LE_PROMPT_EXE "/Users/nitoref/Desktop/powerless/C++/build/bin/powerline"
set -U LE_PROMPT_CONFIG "/Users/nitoref/Desktop/powerless/C++/src/presets/solarized.toml"

function le_prompt --on-event fish_prompt
    set -U LE_PROMPT ($LE_PROMPT_EXE fish $status $LE_PROMPT_CONFIG)
    echo -n "$LE_PROMPT[1]"
end
function fish_prompt
    echo -n "$LE_PROMPT[2]"
end
function fish_right_prompt
    echo -n "$LE_PROMPT[3]"
end
```

```sh
# file: .kshrc

LE_PROMPT_EXE="/Users/nitoref/Desktop/powerless/C++/build/bin/powerline"
LE_PROMPT_CONFIG="/Users/nitoref/Desktop/powerless/C++/src/presets/minimal.toml"
PS1='$(echo -ne "$($LE_PROMPT_EXE ksh $? $LE_PROMPT_CONFIG)")'
```



### configuration

The configuration file is a TOML document  with five sections:

```toml
[segments]
...
[args]
...
[symbols]
...
[theme]
...
[[extension]]
...
```



`[segments]` list the modules to draw in your prompt.

```toml
[segments]

left   = ['perms','dir']
right  = ['time','host','root','jobs','git','status']
bottom = ['shell']
```

Special requirements, or a feature not implemented yet ? Just turn any text, command or environment variable into a segment on your prompt with the `[[extension]]` table array.  If a module is already named that way, it'll get overriden. You may or may not want to call this very software from within an extension. 

```javascript
[[extension]]
name = 'hello'
text = 'world'

[[extension]]
name = 'foo'
env  = 'BAR'

[[extension]]
name  = 'size'
cmd   = 'du -sh | head -c 5'
style = {"bg":155, "fg": 210}
```



`[args]` holds informations on which modules you want to display and their respective options. 

```toml
[args]


left_segments = ['user','perms','pwd','root','exit']
right_segments = ['time','host','git','jobs']
down_segments = []

# [0 - 1] , maximum prompt / input ratio allowed
width_limit = 1

# Margins between each segment, and cursor offset from the prompt
padding_left =   = 1
padding_right =  = 1
padding_end =    = 1

# Force a newline character after prompt even without down modules
force_newline  = false
native_rprompt = false


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
git_notstaged  = "!"
git_conflicted = "×"
git_untracked  = "?"
```



#### Contribute

