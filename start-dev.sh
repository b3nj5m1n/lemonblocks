#!/bin/bash

CLICKABLE_AREAS=30
PANEL_WIDTH=$(xdpyinfo | awk '/dimensions/{print $2}' | cut -d 'x' -f 1)
PANEL_HEIGHT=30
PANEL_HORIZONTAL_OFFSET=0
PANEL_VERTICAL_OFFSET=0
PANEL_FONT="UbuntuMono Nerd Font Mono:size=12"
PANEL_ICON_FONT="Twemoji:size=12"
COLOR_DEFAULT_FG="#f5f5f5"
COLOR_DEFAULT_BG="#aa171517"
UNDERLINE_HEIGHT=3
PANEL_WM_NAME="lemonbar"

# Kill potential instances of lemonbar & lemonblocks
killall "lemonbar"
killall "lemonblocks"

# Make sure the named pipe already exists
mkfifo /tmp/lemonblockspipe

# Start lemonbar
cat "/tmp/lemonblockspipe" | lemonbar -p -a "$CLICKABLE_AREAS" \
    -g "$PANEL_WIDTH"x"$PANEL_HEIGHT"+"$PANEL_HORIZONTAL_OFFSET"+"$PANEL_VERTICAL_OFFSET" \
    -f "$PANEL_FONT" -f "$PANEL_ICON_FONT" -F "$COLOR_DEFAULT_FG" -B "$COLOR_DEFAULT_BG" \
    -u "$UNDERLINE_HEIGHT" -n "$PANEL_WM_NAME" | bash &

sleep 0.5

# Make sure lemonbar is hidden below a fullscreen window
## Bspwm
wid=$(xdo id -a "$PANEL_WM_NAME")
xdo above -t "$(xdo id -N Bspwm -n root | sort | head -n 1)" "$wid"

./bin/lemonblocks
