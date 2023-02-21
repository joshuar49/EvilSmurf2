#!/bin/bash

filename=client_and_server_message.pcap

while true

do

	if [ -f "$filename" ];

	then

	    echo "$filename has found."

	    strings $filename > output.txt

	else

	    echo "filename has not been found"

	fi

	sleep 120

done
