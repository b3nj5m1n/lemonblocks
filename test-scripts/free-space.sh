#!/bin/bash

diskusage=$(df -h | grep -i "/dev/sd" | awk '{print $1 " " $4}' | tr '\n' ' | ')

printf "$diskusage"
