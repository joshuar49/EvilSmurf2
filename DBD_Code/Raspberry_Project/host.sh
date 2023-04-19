#!/bin/bash

new_host="$1"

old_host=$(hostname)

echo "$new_host" > /etc/hostname

sed -i "s/$old_host/$new_host/g" /etc/hosts

sudo reboot now

echo "Hostname changed from '$old_host' to '$new_host'"
