## Raspberry Pi Environment Recreation
- Youtube Video is found here: https://youtu.be/6AaOwTS4LvY

> **NOTE: to downlaod this read me file in raspberry pi you will need to run this command**

```bash 
wget https://github.com/joshuar49/EvilSmurf2/raw/main/DBD_Code/Raspberry_Project/README.md
```
- This shell script will downlaod all the needed files for the project:
```bash 
wget https://github.com/joshuar49/EvilSmurf2/raw/main/DBD_Code/Raspberry_Project/pi.sh
```
> **NOTE: once you have downloaded the `pi.sh` script you will then need to run this command
to execute the shell script:**
```bash 
chmod +x pi.sh
```
- This will allow you to execute the file without issue

- After downloading and runnig the script using the following command: `. pi.sh` or `./pi.sh`
    - If you chose the last option you will need to change directories into "DBD2" like this:
    `cd DBD2` and then you should be good to go!
#### What will be downloaded with this shell script?
- This will download all the **needed binary files for the ASUS Dongle**, all **C 
progams**, the **Makefile**, **README**, **btstart.service**, and a bunch more files that will be used later
> **Note: you have to be a root/super user in order to recreate the environment**

- Use the following command: `sudo -i`
- And if not just use sudo before executing any of the commands
## Updateing your Raspberry Pi

- Update your device using the following:

```bash
sudo apt update && sudo apt full-upgrade
```
- Reboot your device once its been fully upgraded using the following command: `sudo reboot` 
    - This will limit errors from occuring and making the process smoother


#### Download the Needed Bluetooth Related Files

- We need to download the needed bluetooth related files to compile our C files:
```bash
sudo apt-get install bluez && sudo apt-get install bluez libbluetooth-dev
```
```bash
sudo apt-get install libbluetooth-dev
```
## Disabling Onboard Bluetooth and Relocation of Needed Binary Files

- You will then need to move the following files to the following locations with these commands:
```bash
sudo cp rtl8761bu_fw.bin /lib/firmware/rtl_bt

sudo cp rtl8761bu_config.bin  /lib/firmware/rtl_bt
```

- Once this is done we will need to disable our on board bluetooth in order to utilize the ASUS bluetooth dongle
    - To do this we need to edit the `/boot/config.txt` file, to do this we use your prefered text editor, I shall use neovim! :

```bash
sudo nvim /boot/config.txt
```

> **NOTE: at the bottom of the file add the following line of text:**

- `dtoverlay=disable-bt`
    - This will disbale the onboard bluetooth chip, so that you can soley utilize the ASUS BT500 dongle!

- Once this is done press `ctrl o` and then `ctrl x` to write and save to the file with **nano**

- Or `esc :x` on **neovim/vim**

- Afterwards run the following commands:
```bash 
sudo systemctl disable hciuart.service
sudo systemctl disable bluealsa.service
sudo systemctl disable bluetooth.service
```
> **NOTE: some of these changes could do nothing so if nothing happens you can move on to the next command**
- Then you will need to reboot the device in order to apply the changes by using this command: `sudo reboot`

#### Enabling the Bluetooth Dongle

- Once you have updated your bluetooth settings in the past steps you can then see that your bluetooth dongle is working with this command:

```bash
hciconfig
```
- This should show your bluetooth dongle's **MAC address** 

> **NOTE in the event that that your bluetooth dongle is not up and running you will then need to run the following command:**

```bash
sudo hciconfig hci0 up
```

- This will set the bluetooth dongle to be up and running instead of it saying "DOWN"

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

```c 
gcc -o file file.c -lbluetooth
```
- Or use the `make` command if the `Makefile` has been downloaded in the `pi.sh` script!
    - This make fule will compile all the bluetooth programs so that you can make any of your devices 

## Connection Set Up and Terminal Organization

#### DEVICE A SECTION (SERVER)
- you will need 2 terminals PER device so for device A you will need 2 terminals and for device B you will need another 2 terminals
    - If you are running Kali linux you will need to run the `bluetoothd` command so that `bluetoothctl` can work
- In this case device A will be the server

- For device A you will compile `nerw_server.c` and get ready to run the program using this command on the first terminal:
```bash
./new_server.c
```
- Thankfully this should already be compiled with the makefile
- On the second terminal of Device A you will run the following command to enable bluetooth discovery:
```bash 
sudo bluetoothctl
```
> **NOTE: if your bluetooth is not working on another terminal you should run this command to start
the bluetooth daemon:**
```bash
sudo bluetoothd
```

- Now from here you will run the following commands: 

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

- In the first terminal we need to have compiled the `new_client.c` program and have it ready to execute by using this command:

```bash 
./client2
```
- Or `make` to compile
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
`./server2`
- On the **server** machine

**Then run:**
`./client2`  
- On the **client** machine

- And the result will be that you sucessfully sent a message between devices via bluetooth !!!!!
- With the new client and server programs you will be able to send messages constantly between devices


## Making the Server Easier to Detect for Pure Bluetooth Comms 
- Often times it is hard to discover the bluetooth server with the scanning fucntion beign called
- As a result we need to add a couple of files that are included from my section of the Github Repository
    - This is mainly due to the discovery timer on the Pi running out
    - To counter this on the device you wish to make a **Server** you would need to add or change this file:

```bash 
sudo nano /etc/bluetooth/main.conf
```
- Once this is done you can then copy the contents from my `main.conf` file: 
    - Or simply change this variable to 0 
```bash
DiscoverableTimeout = 0
```
- Once that you have editied this file you can then move to `/etc/rc.local`
- Here you can then add these lines of code: 

```bash 
sudo bluetoothctl <<EOF
power on
discoverable on
pairable on
EOF
```
- On boot of the server, it will run these bluetoothctl commands on the Pi so that the already runs the commands
that you ran in the client and server section 
- Then once this is done you can run the `client2` program and be able to discover the server easier! 

## Server Auto Execution of Server Program 
- Making the `server2` prorgam execute once the server boots will be very useful
because this will allow the attacker to have **pure bluetoooth connections** between the clinet and server, thus
making the attack to be low profile
- This very useful when you do not want to connect to a network to `SSH` into the pi 
- To achieve this, you will need to move the btstart.service to the `/etc/systemd/system/`
directoy as `root` 
    - This will allow the device to run the server program on boot! 
- Here is the command you would want to run to move the `.service` file:
```bash 
sudo su 
mv /home/pi/DBD2/btstart.service /etc/systemd/system/
```
- Once you have sucessfully moved the file you can then run these commands
to enable the service on your server device: 
```bash 
sudo systemctl daemon-reload
sudo systemctl enable btstart.service
sudo systemctl start btstart.service
```
- If you wish to see if your bt.start service is running properly run this command: 
```bash
sudo systemctl status btstart.service
```
- And then if you restart the server, wait for it to boot, and then run the ./client2
program you can automatically connect to the server without having to `SSH` into the server!










