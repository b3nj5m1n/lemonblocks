#!/bin/bash

layout=$(setxkbmap -query | grep layout | awk '{print $2}')

printf "%%{A1:~/dotfiles/scripts/keyboard-layout-switcher.sh &:}$layout%%{A1}"
