#!/bin/bash

mkdir DBD2
cd DBD2

echo "Downloading DBD README.txt for convenience\n"
wget https://raw.githubusercontent.com/joshuar49/EvilSmurf2/main/DBD%20Code/Raspberry%20Project/README.md

wget https://git.kernel.org/pub/scm/linux/kernel/git/firmware/linux-firmware.git/plain/rtl_bt/rtl8761bu_fw.bin
wget https://git.kernel.org/pub/scm/linux/kernel/git/firmware/linux-firmware.git/plain/rtl_bt/rtl8761bu_config.bin
echo "Downloading needed Github files from Deep Blue Dev's Repo\n"

wget https://raw.githubusercontent.com/joshuar49/EvilSmurf2/main/DBD%20Code/Raspberry%20Project/new_client.c
wget https://raw.githubusercontent.com/joshuar49/EvilSmurf2/main/DBD%20Code/Raspberry%20Project/new_server.c
wget https://raw.githubusercontent.com/joshuar49/EvilSmurf2/main/DBD%20Code/Raspberry%20Project/Makefile

echo "Files from repo have been downloaded sucessfully!\n"
