#!/bin/bash

diskusage=$(df -h | grep -i "/dev/sdb" | awk '{print $1 " " $4}' | tr '\n' ' | ')

printf "$diskusage"
