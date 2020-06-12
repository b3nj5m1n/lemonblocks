#!/bin/bash

down=$(( $(cat /sys/class/net/enp2s0/statistics/rx_bytes) / 1024**3 ))
up=$(( $(cat /sys/class/net/enp2s0/statistics/tx_bytes) / 1024**3 ))

printf "🔻%dGB 🔺%dGB" "$down" "$up"
