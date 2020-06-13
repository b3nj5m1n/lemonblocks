#!/bin/bash

PANEL_WIDTH=$(xdpyinfo | awk '/dimensions/{print $2}' | cut -d 'x' -f 1)
PANEL_HEIGHT=25
PANEL_HORIZONTAL_OFFSET=0
PANEL_VERTICAL_OFFSET=0
PANEL_FONT="UbuntuMono Nerd"
PANEL_ICON_FONT="Twemoji"
COLOR_DEFAULT_FG="#f5f5f5"
COLOR_DEFAULT_BG="#aa171517"
PANEL_WM_NAME="lemonbar"

killall "bar"

cat "/tmp/lemonblockspipe" | bar -a 12 \
    -g "$PANEL_WIDTH"x"$PANEL_HEIGHT"+"$PANEL_HORIZONTAL_OFFSET"+"$PANEL_VERTICAL_OFFSET" \
    -f "$PANEL_FONT" -f "$PANEL_ICON_FONT" -F "$COLOR_DEFAULT_FG" -B "$COLOR_DEFAULT_BG" \
    -n "$PANEL_WM_NAME" | bash &
