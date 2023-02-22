#!/bin/bash

filename=packets.pcap

while true
do
	if [ -f "$filename" ];
	then
	    echo "$filename has found."
	    strings $filename > output.txt
# Uncomment command below to filter through output.txt for specific strings and send to filter.txt Replace hello with value of choice
#	    grep 'hello' output.txt > filter.txt
	else
	    echo "filename has not been found"
	fi
	sleep 120
done
