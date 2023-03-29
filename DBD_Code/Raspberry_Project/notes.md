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

[pic05](https://github.com/joshuar49/EvilSmurf2/blob/main/DBD_Code/Raspberry_Project/pics/pic04.png)

- I cant wait to show this off in the demo

### Date: 02/21/23 

- There are a lot of small things that i need to do such as: 
    1. I need to FULLY check the readme for any spelling errors
    2. I need to add where to include the new files of:
        - rc.local, and another file 
    3. I would like to make a video but maybe i mgith save it for next time 
    4. I then need to see if i can fix the server scanner function 
        - I might have to make this into a different program or edit the origonal one  


#### 03/23/2023

**I need to do alot of things for this demo**

- I need to implement the read file code from a server out put 
- I need to see how i can execute terminal commands with c so that it prints the output of a 
program to file that is then sent to the user 



#### 03/26/2023

I was finally able to access some SMS messages from my phone but i need to do alot more by testing and trouble shooting 

In addition i need to plan out how i can do things for puretooth and bluesnarfing and merge them together !

**Puretooth Taks** 

-  organize the code a bit better 
- see what else you can add like system commands that can then be use to exe the bluesnarf program 
- Making the puretooth environemnt look alot pretty like what files it should have and other thigns that 
can be incorporated in the program 

**Bluesnarfing** 

- See what changes when trying to print out SMS messages
- make a PDU decoding function that decode the encoded message 
- a way to incorporate this into puretooth 


**Other Items** 

- I need to make video and better diagrams for this project

#### 03/27/2023

**Plan for Today**

- currently i need to have a better understanding of AT commands 
- organize the code that is needed for SMS 
- I need to re wrtie `rw_sms` so that i can test alot more things 

#### 03/29/2023

Today is demo day there are alot of changes that need to be incorped to the demo 

- I need to make a demo video for **Code merger with puretooth and some examples**
- I also need to start adding bluesnarfing to the pi this would be the following: 
    - Adding a dir.sh thing for the program 
    - Adding all the functions needed for the program, it might be on the same program idk 
    - this would need the system command and reading from the buffer!


- I also need to either demo or show the SME hwo i found how to access SMS messages 



































