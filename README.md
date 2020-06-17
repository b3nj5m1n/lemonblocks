# lemonblocks
A status bar generator for lemonbar, inspired by i3blocks and dwmblocks.

![demo](https://i.imgur.com/NkMaIH8.png)

![demo](https://i.imgur.com/5tAUizO.png)


# lemonbar
Lemonbar is a very leightweight bar. The original doesn't support XFT fonts, for that you will have to use a fork, such as [this one](https://aur.archlinux.org/packages/lemonbar-xft-git/), but if you want to have emojis you should probably use [this fork](https://github.com/freundTech/bar).

Lemonbar reads from stdin for the status, it supports clickable areas, the commands will be written to stout.

Lemonblocks aims to make feeding the bar easier. You can define your own modules which you can asign signals. Every time you want to update one of your modules, you can send a signal to the instance of lemonblocks to run the associated command. This means that you don't have to run a script at certain intervals, instead you update it only when necessary.

# Installing
```bash
# Install lemonblocks
sudo make install
```
# Starting

The script called start.sh will start lemonbar with sensible default settings as well as lemonblocks.

The script is moved to /usr/bin when installing, you can call it like this:
```bash
start-lemonbar.sh &
```

# Updating

To update a module:
```bash
# 3 is the signal for your module
pkill lemonblocks -3
```

# Config
You can configure your modules in the file config.txt located at ~/.config/lemonblocks. (Run make config to create the directory and copy the default config)
```
# Seperate values with a , (No space afterwards)
# Interval  Signal  Command Alignment   Initial Status  BgColor FgColor
# Interval of 0 means it will only be updated by signals. NULL means nothing or default value for icons and colors respectively
# Example config:
0,3,🍍,powermenu.sh,l, ,NULL,f8f8ff
1,4,NULL,bspwm.sh,l, ,NULL,f8f8ff
1,5,NULL,cmus.sh,l, ,NULL,f8f8ff
0,6,🔈,volume.sh,r, ,aa1d1f21,f8f8ff
0,7,📁,free-space.sh,r, ,aa1d1f21,f8f8ff
0,8,🐒,layout.sh,r, ,aa1d1f21,f8f8ff
300,10,NULL,network.sh,r, ,aa1d1f21,f8f8ff
30,11,⏰,date.sh,r, ,aa1d1f21,f8f8ff
```
