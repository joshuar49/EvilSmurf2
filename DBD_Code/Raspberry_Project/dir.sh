#!/bin/bash


sudo mkdir -p /dev/bluetooth/rfcomm
sudo mknod -m 666 /dev/bluetooth/rfcomm/0 c 216 0

sudo echo "This is going to be a test"
