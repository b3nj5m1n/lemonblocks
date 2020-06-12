#!/bin/bash

layout=$(setxkbmap -query | grep layout | awk '{print $2}')

printf "$layout"
