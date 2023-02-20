#!/bin/bash

mkdir DBD2
cd DBD2
echo -e "\e[1;34m
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣴⣷⣄⠀⠀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣴⠿⣤⣾⣿⣽⡿⠛⣆⣬⣿⣅⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣶⣿⡟⣟⠁⠀⠀⠀⠉⠁⡀⠀⡚⠉⠀⠈⠹⡶⣄⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⢀⣀⣤⠶⠶⠒⢛⣉⡭⠞⠁⠈⠙⢷⡤⠴⠶⢤⡴⠞⠋⢻⣧⡤⣦⡀⠀⠀⠈⣇⡈⠛⢳⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⣠⡴⠛⣡⠤⠖⠚⠛⠉⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⢾⡏⠁⠀⠀⠙⢦⡀⠀⠨⣧⠀⠀⣿⣦⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⢀⣤⠴⠛⠁⣠⠞⠁⠀⠀⠀⠀⠀⣼⠁⠀⠀⠀⠀⠀⠀⠀⠀⢀⡜⣡⠏⠀⠀⠀⠀⣀⡠⢿⡀⢰⠿⣤⠀⢘⠋⠉⠻⣆⣤⣤⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠋⠁⠀⣠⠞⠁⠀⠀⠀⠀⠀⠀⠀⢻⠀⠀⠀⠀⠀⠀⠀⠀⠀⠚⣰⠋⠀⠀⠀⣰⠞⠁⠀⠀⠉⠁⠀⠹⠗⠻⡆⠀⠀⠻⣯⡉⢣⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⢠⣾⠀⠀⠀⠀⣰⠀⠀⠀⠀⠀⠈⣇⠀⠀⠀⠀⠀⠀⠀⠀⠰⡏⠀⠀⠀⣸⠃⠀⠀⠀⠀⠀⢀⣀⡀⠀⠈⣽⡄⠀⠀⣼⡿⣾⠛⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠘⢻⣤⠀⠀⠀⠹⡆⠀⠠⡄⠀⠀⠘⣆⠀⠀⠀⠀⠀⠀⠀⣶⣧⠀⠀⠀⡇⠀⠀⠀⠀⣠⠞⠉⣸⡿⠿⠿⡶⣽⣦⣶⠿⢦⠈⠳⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠘⢹⡀⠀⠀⠀⠹⣆⠀⠙⠀⠀⠀⠘⢦⡀⠀⠀⠀⠀⠀⠋⣿⠀⠀⣇⡇⠀⢀⠀⣼⠁⡤⠟⠁⣀⣀⣰⣖⣚⠋⠀⠀⢸⠀⠀⢘⣇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⡄⠀⠀⠈⢧⡀⠀⠀⠀⠈⠳⣄⠀⠀⠀⠀⠀⠙⢦⡀⠀⠀⠀⠀⢳⠀⠀⢸⣇⠀⡿⠇⣿⡾⢁⡴⣋⣉⣀⣉⠃⠉⢢⡀⠀⢸⠀⠀⠀⢿⣤⣶⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠙⢦⣀⣀⠀⠙⠢⣄⠀⠀⠀⠈⠳⢦⡀⠀⠀⠀⠀⠙⢦⠀⠀⠀⠀⠀⠀⠀⠉⢀⡇⡇⣷⢃⣏⡾⠉⠀⠀⠉⠙⢶⣶⣿⣄⣿⡄⠀⠀⠘⢿⡍⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠈⠙⠲⢤⣀⡉⠳⠦⣄⡀⠀⠙⠶⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣧⡇⡟⣺⡿⠀⠀⠀⠀⠀⠀⠀⠻⢿⠁⠙⣷⡀⠀⠀⠀⣇⠘⠿⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⢢⣶⢄⡀⠀⠀⠀⠀⠉⠓⠦⠤⣉⣓⠦⣄⡀⠙⠦⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⣿⠿⣧⡀⣾⡇⠀⠀⠀⠀⠀⠀⠀⠀⠈⢷⣄⢹⣿⡄⠀⠀⣿⠤⢤⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠈⠓⢭⣓⠒⠒⠒⠒⠲⠤⣄⡀⠀⠉⠛⠛⠿⠦⣄⣙⠳⢤⡀⠀⠀⠀⠀⠀⠸⡄⠈⢧⢷⢹⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⢯⢏⣿⣶⡄⢹⡇⢈⠟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠉⠓⠲⢤⣤⣀⣀⠀⠉⠓⠲⠤⠔⠶⢴⣤⣭⣉⠀⠈⠓⠦⣄⠀⠀⠀⢻⡄⠈⣞⣆⢳⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⠿⠻⣞⢿⣼⣧⠘⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠘⣶⣤⣀⠀⠀⠀⠀⠉⠙⠦⣤⣤⣀⣤⣤⣤⣀⣀⡀⠉⠳⢦⣀⠀⠀⠀⠀⠀⠙⣄⡈⢯⢪⡻⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⢾⣽⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⢹⣦⡍⠓⠶⠤⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠲⠤⣍⣙⣳⣦⡀⠀⠀⠀⠙⠶⣷⣹⣟⢷⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
    ____                        ____   __                ____                   
   / __ \ ___   ___   ____     / __ ) / /__  __ ___     / __ \ ___  _   __ _____
  / / / // _ \ / _ \ / __ \   / __  |/ // / / // _ \   / / / // _ \| | / // ___/
 / /_/ //  __//  __// /_/ /  / /_/ // // /_/ //  __/  / /_/ //  __/| |/ /(__  ) 
/_____/ \___/ \___// .___/  /_____//_/ \__,_/ \___/  /_____/ \___/ |___//____/  
                  /_/                                                           
⠙⢦⣀⠀⠀⠀⠀⠀⠀⠀⠀⠠⣤⣀⣀⠙⢦⡀⠀⠈⠉⠓⠢⢤⣀⠀⠘⠿⢤⣄⡀⠀⠀⠀⠀⠀⠉⠒⢦⣄⣈⡉⠒⠦⣤⣀⠀⠀⠀⠉⠙⠒⠲⢤⣤⣀⡀⠀⠀⠀⠀⠀⠀⠀⠁
⠀⠀⠉⠓⠚⠓⠦⣄⡀⠀⠀⠀⠉⠑⠺⣭⡑⠛⠂⠀⠀⠀⠀⠀⠈⠙⠲⢦⣀⣈⣙⠓⠦⣄⡀⠀⠀⠀⠀⠀⠉⠉⠙⠒⠒⠛⠛⠂⠀⠀⠀⠀⠀⠀⠀⠈⠉⠙⠓⠒⠲⠦⠤⣤⣤
⠀⠀⠀⠀⠀⠀⠀⠀⠉⠓⢦⡀⠀⠀⠀⠀⠉⠓⠦⣀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠈⠉⠑⠾⢍⣦⣄⠀⠀⠀⠀⠀⠀⠀⠤⠤⠤⠤⠤⢤⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢳⣚⣇⡀⠀⠀⠀⠀⠀⠈⠙⠲⢤⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣈⣛⣷⣤⣀⣀⣀⣀⣀⣀⣀⣀⣀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠙⠓⠲⠤⠤⣄⣀⠀⠀⠈⠙⠲⠤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣇⣉⣡⣛⣁⣹⣛⣉⣿
\e[0m"

echo "Downloading DBD README.txt for convenience"
wget https://github.com/joshuar49/EvilSmurf2/raw/main/DBD_Code/Raspberry_Project/README.md

echo "Downloading BT500 Binary Files"
wget https://git.kernel.org/pub/scm/linux/kernel/git/firmware/linux-firmware.git/plain/rtl_bt/rtl8761bu_fw.bin
wget https://git.kernel.org/pub/scm/linux/kernel/git/firmware/linux-firmware.git/plain/rtl_bt/rtl8761bu_config.bin

echo "Downloading needed Github files from Deep Blue Dev's Repo"

wget https://github.com/joshuar49/EvilSmurf2/raw/main/DBD_Code/Raspberry_Project/new_client.c
wget https://github.com/joshuar49/EvilSmurf2/raw/main/DBD_Code/Raspberry_Project/new_server.c
wget https://github.com/joshuar49/EvilSmurf2/raw/main/DBD_Code/Raspberry_Project/Makefile
wget https://github.com/joshuar49/EvilSmurf2/raw/main/DBD_Code/Raspberry_Project/btstart.service

wget https://github.com/joshuar49/EvilSmurf2/raw/main/DBD_Code/Raspberry_Project/main.conf 
wget https://github.com/joshuar49/EvilSmurf2/raw/main/DBD_Code/Raspberry_Project/rc.local 
wget https://github.com/joshuar49/EvilSmurf2/raw/main/DBD_Code/Raspberry_Project/scanner.h 

echo "Files from repo have been downloaded sucessfully!"

