USAGE="Usage: ./camera_stream.sh CLIENT_IP CLIENT_PORT"
printf "$USAGE\n"

# Using UDP
#raspivid -n -w 854 -h 480 -fps 20 -t 9999999 -o - | nc -u $1 $2


# Using TCP
raspivid -n -w 480 -h 320 -fps 20 -hf -t 9999999 -o - | nc $1 $2