# lemonblocks
## A status bar generator for lemonbar
## Inspired by i3blocks and dwmblocks

# lemonbar
Lemonbar is a very leightweight bar. The original doesn't support XFT fonts, for that you will have to use a fork, such as [this one](https://aur.archlinux.org/packages/lemonbar-xft-git/), but if you want to have emojis you should probably use [this fork](https://github.com/seitokaichou/bar).

Lemonbar reads from stdin for the status, it supports clickable areas, the commands will be written to stout.

Lemonblocks aims to make feeding the bar easier. You can define your own modules (At compile time, at least for now) which you can asign signals. Every time you want to update one of your modules, you can send a signal to the instance of lemonblocks to run the associated command. This means that you don't have to run a script at certain intervals, instead you update it only when necessary.

Lemonblocks writes to a named pipe which you have to pipe into lemonbar. An example command to start lemonbar looks like this:
```bash
# Cat from the named pipe as input, set a font for text and a font for emojis, as well as a default background & foreground color
cat /tmp/lemonblockspipe | bar -p -f "UbuntuMono Nerd" -f "Twemoji" -B "#aa000000" -F "#ff0066"
```
To update a module:
```bash
# 3 is the signal for your module
pkill lemonblocks -3
```

# Config
The config is located in config.h, every time you change something you need to recompile the program.
```c
// Icon, Command, Signal (> 2)
static const block blocks[] = {
	{"🐨",	"./test-scripts/date.sh",	3},
	{"🦏",	"./test-scripts/free-space.sh",	4},
};

// Maximum length for the output of a module
static int MAX_LEN = 200;
// The delimiter between modules
static char *DELIM = "   |   ";
// The delimiter between the icon and the command output
static char *DELIM_ICON = "  ";
```
