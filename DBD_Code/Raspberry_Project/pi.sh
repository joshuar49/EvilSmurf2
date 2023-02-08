#!/bin/bash

mkdir DBD2
cd DBD2

echo "Downloading DBD README.txt for convenience"
wget https://github.com/joshuar49/EvilSmurf2/raw/main/DBD_Code/Raspberry_Project/README.md

wget https://git.kernel.org/pub/scm/linux/kernel/git/firmware/linux-firmware.git/plain/rtl_bt/rtl8761bu_fw.bin
wget https://git.kernel.org/pub/scm/linux/kernel/git/firmware/linux-firmware.git/plain/rtl_bt/rtl8761bu_config.bin
echo "Downloading needed Github files from Deep Blue Dev's Repo"

wget https://github.com/joshuar49/EvilSmurf2/raw/main/DBD_Code/Raspberry_Project/new_client.c
wget https://github.com/joshuar49/EvilSmurf2/raw/main/DBD_Code/Raspberry_Project/new_server.c
wget https://github.com/joshuar49/EvilSmurf2/raw/main/DBD_Code/Raspberry_Project/Makefile
wget https://github.com/joshuar49/EvilSmurf2/raw/main/DBD_Code/Raspberry_Project/btstart.service 

echo "Files from repo have been downloaded sucessfully!"
