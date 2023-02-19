# Date: 02/15/2023

- I found out a way to make the discoverable timer 0 
- This might need to be editied later to make the server discrete
```bash 
sudo nano /etc/bluetooth/main.conf
```
- Then look for the line that says this: 
```bash
DiscoverableTimeout = 0
```
here we need to uncomment the line like this: 

![Pic1](/home/kali/gitt/EvilSmurf2/DBD_Code/Raspberry_Project/pics/pic01.png)

- Since we are setting the discoverable timer to zero this means that we will
have teh device discoverable forever
- To have commands ran on bluetoothctl we can addd these commands to a rc.local file
located at `/etc/rc.local`

This would be the code we would enter which are just the commands from 
bluetoothctl
```bash 
sudo bluetoothctl <<EOF
power on
discoverable on
pairable on
EOF
```
- Once that this is done i recomend to `sudo chmod +x /etc/rc.local`
- Another thing we can do to remove any uncertanty is to add this command to 
trust the mac address of the client so that they will always strust each other as well
```bash 
trust mac address 
```
#### Working on the scan function
- I managed to make the fucntion return the address but the thing is that this 
is not engough it returns the last stored address that is scanned by the fucntion 
- My solution to this would be to make a 2d array to store an array of mac address 
- The thing that i dont know is that if lets say i have an addres sof like idk
3 addresses that are scaanned i don t know if initializing it.... 
maybe a counter would be needed for this 
- then i init the 2d array witht the amount of addresses found and store them !

Here is a snip of the progam btscanf.c working:
![pic3](/home/kali/gitt/EvilSmurf2/DBD_Code/Raspberry_Project/pics/pic03.png)

- I made alot more changes to the bluetooth scanner fucntion that will 
allow us to see a max of 4 mac addresses scannded from the function
- For the next implementation i need to be able to add it to the client 
and server so that they can utilize the function for: 
    - the client to connect to the server 
    - or the server to connect to the victim! 
#### Plans for the rest of the week

1. I need to make both the client and server call the btscanner func 
2. Add bluesnarffing features to the programs

### Date: 02/16/2023

- Made some updates to the shell script
    - Immma think of some new things to add to it to make it 
    look more interesting like a logo or something
- I need to make some changes to the README to incorporate the the new files 
and where they need to be located
- Ill see if someone in the team can help me spell check the readme for the 
presentation for next week 
- After this i need to add the btscan function to the main client and
server program to assign mac addresses
- Lastly i need to record a new video for the presentation

### Date: 02/19/23 

- My main goal for this weekend was to better modify the bluetooth scanner fucntion 
so that it is able to scan for devices, append those devices to an array, and have the function return 
the index of the array chosen by the user

- Now that i have accomplished this through cases and finding ways for a function to return the array
i then started to implement the function in the client program so that it is able to scan for devices so 
that the user can specify which server they want to connect to
    - This will be needed later so that a user can connect to muliple bluetooth servers so that they can 
    connect to them and then commence attacks on the target devices that the server will use! 

- All the changes have been made to the client code and i will begin to make changes to the server soon 
    - This was that if the cleint wants the server to attack the 3rd device scanned by the function, 
    we will be able to choose which one the user wants to attack 
- I will look into this a bit later in the week but so far i am happy with the new feature! 

**Here is a snip of it all working:**

[pic05](/home/kali/gitt/EvilSmurf2/DBD_Code/Raspberry_Project/pics/pic04.png)

- I cant wait to show this off in the demo
