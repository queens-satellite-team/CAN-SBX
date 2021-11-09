#!/bin/bash
FILE="/home/pi/payload_watchdog/temp.dog"
while true 
do 
	if test -f "$FILE"; then
		echo "File Exists"
		rm -f "$FILE"
	
	else
		echo "restarting"
		sudo python3 /home/pi/CAN-SBX/payload/PiCamCode.py >2&1> "logs.txt"
	fi
	for i in {1..60}
		do
			sleep 1
		       echo $i
	       done	       
done
