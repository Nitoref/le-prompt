Yet another fully featured theme for your shell.
This time with full left, right and multi-line prompt support for bash, tcsh, zsh and fish.

This theme is for people that love their good ol' shell, or don't want/can switch to fish or zsh - but still want a wonderfull looking shell like all the cool kids. It's also a theme for people that have to work with different shells, but want a unifying experience.

### Why another one ?

* Fast.
* Fully shell agnostic.
* Heavily and easily customizable.
* Extensible.

### Installation

#####Requisites

 `xterm-256color`compatible terminal for colors as well as [powerline fonts](https://github.com/powerline/fonts) and / or [nerd fonts](https://github.com/ryanoasis/nerd-fonts) are highly recommended to fully enjoy this software.

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

```bash
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

```bash
# file: .(t)cshrc

set POWERLINE_EXE     = "path/to/powerline"
set POWERLINE_CONFIG  = "path/to/config.json"
set POWERLINE_COMMAND = '$POWERLINE_EXE $0 $? $POWERLINE_CONFIG'
alias precmd 'set prompt="`$POWERLINE_EXE csh $? $POWERLINE_CONFIG`"'

```

###### fish 

```bash
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

The configuration file is JSON document (with comments accepted) with three objects:

`extension`Special requirements or a feature not implemented yet ? Just turn any command into a module on your prompt.  If a module is already named that way, it'll get overriden.

```javascript
"extension" : {
		"size" : {
				"command" : "du -sh | head -c 5",
      	"style" : {"bg":155, "fg": 210}
		}
}
```



 `args`holds informations on which modules you want to display and their respective options. 

```javascript
"args": {
		"left_segments": ["user","perms","pwd","root","exit"], // Left aligned modules
		"right_segments": ["time","host","git","jobs"]         // Right aligned modules
  	"default_user" : "you",           // If set, hides username module when equals
  	"default_host" : "your-machine",  // If set, hides host module when equals
  	"max_prompt_width"  : 0,    // 
  	"max_segment_width" : 0,    //
  	"request_timeout" : 1000,   // 
  	"time_format" : "%H:%M:%S", //
  	"cwd_max_depth" : 4,       // Maximum path depth in pwd module.
  	  
  	// Set of aliases to shorten pwd module
  	"path_aliases" : {
				"/usr/local/bin" : "bin",
				"/Downloads/Series" : "hold on"
		}
}
```

 `symbols` lets you customize any symbol, from versionning informations to shell 