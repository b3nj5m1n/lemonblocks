#!/bin/bash

down=$(( $(cat /sys/class/net/enp2s0/statistics/rx_bytes) / 1024**2 ))
up=$(( $(cat /sys/class/net/enp2s0/statistics/tx_bytes) / 1024**2 ))

printf " 🔻%dMiB 🔺%dMiB " "$down" "$up"
