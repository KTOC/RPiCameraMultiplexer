#!/bin/bash

# This shall be started first
USAGE="Usage: camera_read_stream.sh listening_port"
printf "$USAGE\n"
# UDP
# nc -l -p $1 | mplayer - -fps 20 -cache 2048

# trap ctrl-c and call ctrl_c()
trap ctrl_c INT
function ctrl_c() {
        echo "** Trapped CTRL-C"
        exit 1
}

# TCP
while true; do
	nc -l -p $1 | mplayer -fps 200 -demuxer h264es -
	echo "---Disconnected---"
done
