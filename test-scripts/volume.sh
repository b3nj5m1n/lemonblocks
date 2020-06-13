#!/bin/bash

volume=$(pactl list sinks | grep '^[[:space:]]Volume:' | \
    head -n $(( $SINK + 1 )) | tail -n 1 | sed -e 's,.* \([0-9][0-9]*\)%.*,\1,')

printf "%%{A1:amixer set Master toggle; pkill lemonblocks -6:}\
%%{A4:amixer -q sset Master 1%%+; pkill lemonblocks -6:}\
%%{A5:amixer -q sset Master 1%%-; pkill lemonblocks -6:}\
$volume%%\
%%{A1}%%{A4}%%{A5}"
