!/bin/bash

 if pgrep node > /dev/null 2>&1
	then 
		echo "Node already running"
else
    echo "Restarting Node:     $(date)" 
	if pgrep redis-server > /dev/null 2>&1
		then
			redis-server &
	fi

	node ~/workspace/OceansOfThings/IoT_Server/NodeMQTT/mosca-app.js &
	sleep 7     
fi
