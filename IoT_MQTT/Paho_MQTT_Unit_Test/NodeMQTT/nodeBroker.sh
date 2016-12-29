!/bin/bash

 if pgrep node > /dev/null 2>&1
	then 
		echo "Node already running"
else
    echo "Restarting Node:     $(date)" 
	node NodeMQTT/mosca-app.js &
	sleep 7     
fi
