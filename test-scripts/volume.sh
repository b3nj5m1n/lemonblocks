#!/bin/bash

volume="$(amixer sget Master | grep 'Right:' | awk -F'[][]' '{ print $2 }' | cut -d '%' -f 1)"

printf "$volume%% "
