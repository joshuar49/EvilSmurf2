## Raspberry Pi Environment Recreation
- Youtube Video is found here: https://youtu.be/6AaOwTS4LvY

> **NOTE: to downlaod this read me file in raspberry pi you will need to run this command**

```bash 
wget https://raw.githubusercontent.com/joshuar49/evilsmurf2/main/dbd%20code/raspberry%20project/readme.txt
```
- this file will help you recreate the environment that i have
    - this involves downloading the pi.sh from our github page using the following command:
```bash 
wget https://raw.githubusercontent.com/joshuar49/evilsmurf2/main/dbd%20code/raspberry%20project/pi.sh
```

- after downloading and runnig the script using the following command: `. pi.sh`
> **note: you have to be a root/super user in order to recreate the environment**
- use the following command: `sudo -i`

## updateing your raspberry pi

- update your device using the following:

```bash
sudo apt update && sudo apt full-upgrade
```
- reboot your device once its been fully upgraded using the following command: `sudo reboot` 
    - this will limit errors from occuring and making the process smoother


#### download the needed bluetooth related files

- once you logged back into your device become a root user using: `sudo -i`

- then we need to download the needed bluetooth related files to compile our c files:
```bash
sudo apt-get install bluez && sudo apt-get install bluez libbluetooth-dev
```
```bash
sudo apt-get install libbluetooth-dev
```
## Disabling onboard bluetooth and relocation of needed binary files

- you will then need to move the following files to the following locations with these commands:
```bash
sudo cp rtl8761bu_fw.bin /lib/firmware/rtl_bt

sudo cp rtl8761bu_config.bin  /lib/firmware/rtl_bt
```

- once this is done we will need to disable our on board bluetooth in order to utilize the asus bluetooth dongle
    - to do this we need to edit the `/boot/config.txt` file, to do this we use your prefered text editor but i shall use neovim!:

```bash
sudo nvim /boot/config.txt
```

> **NOTE: at the bottom of the file add the following line of text:**

- `dtoverlay=disable-bt`
    - this will disbale the onboard bluetooth chip, so that you can soely utilize the asus bt500 dongle!

- once this is done press `ctrl o` and then `ctrl x` to write and save to the file with *nano*

- or `esc :x` on `neovim/vim`

- afterwards run the following commands:
```bash 
sudo systemctl disable hciuart.service
sudo systemctl disable bluealsa.service
sudo systemctl disable bluetooth.service
```
> **NOTE: some of these changes could do nothing so if nothing happens you can move on to the next command**
- then you will need to reboot the device in order to apply the changes by using this command: `sudo reboot`

#### Enabling the Bluetooth Dongle

- Once you have downloaded and updated your bluetooth settings in the past steps you can then see that your bluetooth dongle will appear using the `hciconfig`
command like this

```bash
hciconfig
```
- This should show your bluetooth dongle's **MAC address**, depending on what device you will be setting up as a
server or client this **MAC address** will be useful

> **NOTE in the event that that your bluetooth dongle is not up and running you will then need to run the following command:**

```bash
sudo hciconfig hci0 up
```

- This will set the bluetooth dongle to be up and running

#### Compilation of the C prorgams

- Depending on which of the two raspberry pi devices you want to make a server or client, then compilation will be similar with one small difference

- Before we continue in compilation we need to establish what device will be a server and a client
If device A will be the server, then we need to know the dongle's MAC address using the following command: `hciconfig`

- This will show your bluetooth devices information and will display it's MAC address it should look something like this:


```bash 
pi@shade:~ $ hciconfig
hci0:   Type: Primary  Bus: USB
        BD Address: 58:11:22:62:56:CD  ACL MTU: 1021:6  SCO MTU: 255:12
        UP RUNNING PSCAN
        RX bytes:57610 acl:135 sco:0 events:1414 errors:0
        TX bytes:38834 acl:129 sco:0 commands:656 errors:0
```

> **NOTE: "BD Address:" is the MAC address of your dongle**
- You will then copy this mac address, edit the client.c file on Device B and enter it into the following line of code present in the file:
```c 
char dest[18] = "REPALCE AND ENTER MAC ADDRESS HERE"; 
// this is the address for your bluetooth device!!!!! 
//remember to add the MAC address before compiling
```

- it should then look something like this but your MAC address will be different!
```c 
char dest[18] = "58:11:22:62:56:CD";
```

- Then you can freely compile the C files on each device!

> **NOTE: when compiling any of the two C files you will need to run the following command:**

```c 
gcc -o file file.c -lbluetooth
```
- Or use the `make` command if the `Makefile` has been downloaded in the `pi.sh` script!

## Connection Set Up and Terminal Organization

#### DEVICE A SECTION (SERVER)
- you will need 2 terminals PER device so for device A you will need 2 terminals and for device B you will need another 2 terminals
    - If you are running Kali linux you will need to run the `bluetoothd` command so that `bluetoothctl` can work
- In this case device A will be the server

- for device A you will compile `rf_server.c` and get ready to run the program using this command on the first terminal:
```bash
./rf_server
```

- On the second terminal of Device A you will run the following command to enable bluetooth discovery:
```bash 
sudo bluetoothctl
```
- here you will run the following commands: 

```bash 
discoverable on
pairable on
agent on
default-agent
```
- These commands will do the following:
1. Make the agent or the bluetooth device discoverable to other devices
2. Make the device be able to pair with other devices 
3. Iniitalize the agent or in this case the Bluetooth Dongle
4. Lastly the last command will make bleutooth dongle the default agent on the device 

#### DEVICE B SECTION (CLIENT)

- In the first terminal we need to have compiled the `rf_client` c program and have it ready to execute by using this command:
```bash 
./rf_client
```

- On the second terminal for Device B we need to use the same command to bring up bluetooth:
```bash 
sudo bluetoothctl
```

- Once you have ran this command you will then need to run the same 4 commands like we did for Device A
```bash 
discoverable on
pairable on
agent on
default-agent
```

## Pairing Both Devices and Program Execution

- Since Device A is the server you will need to run this command on Device A's bluetooth terminal:
```bash 
scan on
```
- This command will scan devices that are near Device A

- On Device B you will run the client program if Device B is not appearing in Device A's bluetooth terminal 
- Once Device A discovers Device B, the MAC address to Device B's bluetooth dongle will appear
- On Device A's bluetooth terminal, you will then run this command:
```bash 
pair MAC ADDRESS
```
- For this example, I will run this:
```bash 
pair 58:11:22:62:56:E3
```
- Do this multiple times until both devices are connected to each other
    - Once the devices are connected you will need to pair them by typing `yes` on both devices **when prompted**
- Once this is done on the Device's corresponding program execution terminals you will follow these steps:

**Run:**
`./rf_server`
- on the **server** machine

**Then run:**
`./rf_client`  
- on the **client** machine

- And the result will be that you sucessfully sent a message between devices via bluetooth !!!!!
- With the new client and server programs you will be able to send messages constantly between devices
    - As the project goes on I will be able to use pure bleutooth commuication between devices to maintain 
    a low profile

