#!/bin/bash

volume="$(amixer sget Master | grep 'Right:' | awk -F'[][]' '{ print $2 }' | cut -d '%' -f 1)"

printf "%%{A1:amixer set Master toggle; pkill lemonblocks -6:}\
%%{A4:amixer -q sset Master 1%%+; pkill lemonblocks -6:}\
%%{A5:amixer -q sset Master 1%%-; pkill lemonblocks -6:}\
$volume%% \
%%{A1}%%{A4}%%{A5}"
