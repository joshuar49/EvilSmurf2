#!/bin/bash

while true
do
	# Searches for all pcap files in directory
	for x in *.pcap; do
	# Removes extension from orginal filename used to name output file
	strings $x > "${x:0:${#x}-5}_output.txt"
	# Moves analyzed pcap file out of folder
	mv $x /home/dbd/savedpcap 
	# Uncomment command below to filter through output.txt for specific strings and send to filter.txt Replace hello with string of choice
	grep 'hello' "${x:0:${#x}-5}_output.txt" > "${x:0:${#x}-5}_filter.txt"
	done
	sleep 120
done
