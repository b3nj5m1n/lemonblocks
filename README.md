# lemonblocks
A status bar generator for lemonbar, inspired by i3blocks and dwmblocks.

![demo](https://i.imgur.com/DuCCc2G.png)

![demo](https://i.imgur.com/J1X7mQu.png)


# lemonbar
Lemonbar is a very leightweight bar. The original doesn't support XFT fonts, for that you will have to use a fork, such as [this one](https://aur.archlinux.org/packages/lemonbar-xft-git/), but if you want to have emojis you should probably use [this fork](https://github.com/freundTech/bar).

Lemonbar reads from stdin for the status, it supports clickable areas, the commands will be written to stout.

Lemonblocks aims to make feeding the bar easier. You can define your own modules (At compile time, at least for now) which you can asign signals. Every time you want to update one of your modules, you can send a signal to the instance of lemonblocks to run the associated command. This means that you don't have to run a script at certain intervals, instead you update it only when necessary.

There is now a premade script providing some sensible settings to start lemonbar automatically.
```bash
# Start lemonbar with default colors, two fonts (Default & Emojis), a set size, etc.
./start-lemonbar.sh
```
To update a module:
```bash
# 3 is the signal for your module
pkill lemonblocks -3
```

# Config
The config is located in config.h, every time you change something you need to recompile the program.
```c
// Icon, Command, Interval, Signal (Except 2 & 9), Foreground Color, Background Color, Align (Needs to be specified in the correct order here, otherwise modules will overlap)
static const block blocks[] = {
	{"🍍",	"./test-scripts/powermenu.sh", 0, 3, "#f8f8ff", "", 'l'},
	{"",	"./test-scripts/bspwm.sh", 1, 4, "#f8f8ff", "", 'l'},
	{"",	"./test-scripts/cmus.sh", 1,	5, "#f8f8ff", "", 'c'},
	{"🔈",	"./test-scripts/volume.sh", 0,	6, "#f8f8ff", "", 'c'},
	{"",	"./test-scripts/layout.sh", 0,	7, "#f8f8ff", "", 'r'},
	{"",	"./test-scripts/network.sh", 60,	8, "#f8f8ff", "", 'r'},
	{"",	"./test-scripts/date.sh", 60,	10, "#f8f8ff", "", 'r'},
};

// Maximum length for the output of a module
static int MAX_LEN = 1500;
// The delimiter between modules
static char *DELIM = "   ";
// The delimiter between the icon and the command output
static char *DELIM_ICON = " ";
```
