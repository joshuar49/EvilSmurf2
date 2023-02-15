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

