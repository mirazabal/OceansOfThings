#!/bin/bash

# activate this from another shell, and watch the numbers: $socat -d -d PTY PTY &
#http://www.xappsoftware.com/wordpress/2013/10/07/using-virtual-serial-ports-on-linux-ubuntu/

file="/home/mikel/workspace/OceansOfThings/IoT_Node/sensors/GPS/portSimulator/GPS_data.txt"

while IFS='' read -r line || [[ -n "$line" ]]; do
    echo "$line" > /dev/pts/22
	sleep 1
done < "$file"

#echo " Hello World" > /dev/pts/19
#echo "from script" > /dev/pts/19

