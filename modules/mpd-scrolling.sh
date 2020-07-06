#!/bin/bash

# Polybar script for getting the current song from cmus

# Call cmus-remote -Q to get available information about the current song
song=$(mpc -f "%artist% - %title%" current)
info=$(mpc)
# Store the return value to check if cmus is running
retval=$?

if [ $retval -ne 0 ]; then
    # If the return value is not 0, then echo nothing, since cmus is not running
    printf " "
    exit
else
    # Cmus is running, so find out if it's playing or paused and echo the corresponding glyph
    if grep -q "playing"  <<< "$info"
    then 
        printf "";
    else
        printf "paused";
        exit
    fi
fi

chrlen=${#song}

# How long to make the text before starting to scroll
maxlen=25

if [[ $chrlen -ge $maxlen ]]; then
    # Read offset from file
    offset="$(($(cat /tmp/mpdoffset | head -n 1)))"
    # Add one
    offset="$(($offset + 1))"
    # Test if offset should be reset
    if [[ "$song" != "$(sed "2q;d" /tmp/mpdoffset)" ]]; then
        rm /tmp/mpdoffset
        offset=0
    fi
    if [[ $(($offset + $maxlen - 1)) -ge $chrlen ]]; then
        rm /tmp/mpdoffset
        offset=0
    fi
    # Write offset back to file
    echo -e "$offset\n$song" > /tmp/mpdoffset
    song="${song:$offset:$maxlen}"
fi


# Parse the info to get the progress in %
# total=$(echo "$info" | sed -r "s/duration //;t;d")
# progr=$(echo "$info" | sed -r "s/position //;t;d")
# perc=$(awk -v n="$total" -v m="$progr" 'BEGIN{ print int(( m/n )*100) }')
perc=$(echo "$info" | grep -oie "([[:digit:]]*%)" | tr '%' ' ' | tr '(' ' ' | tr ')' ' ')
chrlen=${#song}
perc_chr=$(awk -v n="$chrlen" -v m="$perc" 'BEGIN{ print int( n*(m/100)) }')

# What to put at the beginning of the string
# b="\e[31m"
b="%%{F#ff0066}"
# What to put in the middle of the string
# m="\e[0m"
m="%%{F-}"
# What to put at the end of the string
# e="\e[0m"
e=""

song="$b${song:0:$perc_chr}$m${song:$perc_chr:$chrlen}$e"
printf "$song"
