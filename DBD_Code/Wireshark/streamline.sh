#!/bin/bash

while true
do
	for x in *.pcap; do
	strings $x > "${x:0:${#x}-5}_output.txt"
	# Configure your directory here
	mv $x /home/dbd/SavedPCAP
	# Uncomment command below to filter through output.txt for specific strings and send to filter.txt Replace hello with value of choice
	grep 'hello' "${x:0:${#x}-5}_output.txt" > "${x:0:${#x}-5}_filter.txt"
	done
	#Choose reload time here
	sleep 120
done
