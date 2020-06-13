#!/bin/bash

### Query bpswm for desktop ids
# Query bspwm for all desktops
all=$(bspc query -D)
# Query bspwm for all desktops that have something on them
occupied=$(bspc query -D -d .occupied)
# Query bspwm for all desktops that don't have something on them
notoccupied=$(bspc query -D -d .\!occupied)
# Query bspwm for the current desktop
current=$(bspc query -D -d .focused)

### Color definitions
# Default background color
cdBACKGROUND="#1d1f21"
# Default foreground color
cdFOREGROUND="#f8f8ff"
# Default underline color
cdUNDERLINE="$cdBACKGROUND"
# Occupied underline color
coUNDERLINE="#00ff99"
# Focused underline color
cfUNDERLINE="#ff0066"

### Other variables
# Padding will be applied to both sides
padding="  "
# u = underline, o = overline
uoline="o"

# This variable will contain the output of the command
result=""
# Add default background color
result="$result%%{B$cdBACKGROUND}"
# Add default foreground color
result="$result%%{F$cdFOREGROUND}"
# Enable underline
result="$result%%{+$uoline}"
# Set command on scroll-up
result="$result%%{A4:bspc desktop -f prev:}"
# Set command on scroll-down
result="$result%%{A5:bspc desktop -f next:}"

# Loop over all lines (Desktop id's) of the all variable
while IFS= read -r line; do

    # Get the name of the current desktop
    name=$(bspc query -d "$line" -D --names)

    # What underline color to choose
    underline=""

    # Check if the current desktop is occupied
    # if [[ "$occupied" == *"$(bspc query -d "$line" -D)"* ]];
    if [[ "$occupied" == *"$line"* ]];
    then
        # The desktop is occupied, use occupied underline color
        underline="$coUNDERLINE"
    else
        # The desktop is not occupied, use default underline color
        underline="$cdUNDERLINE"
    fi

    # Check if the current desktop is focused
    if [[ "$current" == *"$line"* ]];
    then
        # The desktop is focused, use focused underline color
        underline="$cfUNDERLINE"
    fi

    # Add underline formatter to result
    result="$result%%{U$underline}"

    # Add click event
    result="$result%%{A1:bspc desktop -f $name:}"

    # Add padding
    result="$result$padding"

    # Add the name to the ouput
    result="$result$name"

    # Add padding
    result="$result$padding"

    # Close click event
    result="$result%%{A1}"

    # Close underline formatter
    result="$result%%{U-}"

done <<< "$all"

# Disable underline
result="$result%%{-$uoline}"
# Disable command on scroll-up
result="$result%%{A4}"
# Disable command on scroll-down
result="$result%%{A5}"

printf "$result"
