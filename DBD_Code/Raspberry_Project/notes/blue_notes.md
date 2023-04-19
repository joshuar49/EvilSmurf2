# Note for Bluesnarfer program
- Here is the code so far: 
> **NOTE: this is going to be for the signal header file!** 
- Signals are used to tell a process of an event or an interrupt ! 
- SIGINT is a interrupt signal MOST OF THE TIME think about when ou press ctrl c this will cause SIGINT to be called! 
- SIGSEGV is a segmenation fault signal ! this happens when a program tries to access memory when 
its not ment to
i 

i need a program to check fofr new pcap files
i need a progam to take all teh pcap files from one dir
and copy them over to a new dir
if dir exsists ask user if they wish to copy the files to teh dir 
else exit 


- Another interesting find that might be exploitable would be the `bt_get_remote_name` function 
    - This function gets the name of a device with a mac address of the device 
    - It sends a SDP request to the device, and retunrs the name as a string 
    - If not successful it will return a error code 


#### hci_conn_info_req 

- this is a structure that is found in the hci.h header file and looks like this: 
```c
struct hci_conn_info_req {
	bdaddr_t bdaddr;
	uint8_t  type;
	struct hci_conn_info conn_info[];
};
```
- this is mainly used when a program needs to get information about a bluetooth connection !
- Once a bluetooth device makes a connection it is then assigned a unique connection handle called 
**connection id** 
- The struct is used to query the stack for bt info about the connection 
- It has fields that can retrieve information about an active bluetoth connection
    - This type of information are:
    - Bluetooth device address of a remote device, 
    - connection interval
    - connection latency 
    - connection supervision timeout
- this can also optimize the performance of a device !

#### hci_create_connection function

Located in the hci.h header file 
- Used to init a connection between 2 devices
- makes the host specify the bt device addr params, these are things like: 
    - connection interval
    - window 

- once the connection is established the host can comm with the remote dev using a protocol
    - SPP serial port profile 
    - GATT generic attribute profile

**Here is a example of how the function is defined: ** 
```c 
int hci_create_connection(int dd, bdaddr_t *bdaddr, uint16_t ht, uint8_t hci_role, uint16_t clock_offset, uint8_t allow_role_switch);

```

**Here is the code from the snarfer:** 
```c
if ((cc = hci_create_connection(dd, &bdaddr,htobs(HCI_DM1 | HCI_DH1), 0, 0,(void *)&handler, 25000)) < 0)
```

- for the third param ht, in the snarfer code, htobs(HCI_DM1 | HCI_DH1) sets ht to 0x000a
- that address presents the 0x000a 
- this means that the packet length is set to 27 bytes 

**Fourth Param** 

- the first 0 sets the ***hci_role*** to HCI_ROLE_MASTER
- This means that the local device will be laptop 

**Fith Param**

- the second zero to the clock 
- this is the clock sync between devices, this makes sure that data is transmitted and recieved correctly
- used to sync timing of data transmission
- zero means clock offset is not known or none existant
    - if the device is close to each other then the offset would really need to be anything else 
    - this might need to change if we are working with devices from a long range tho
    - in that case it is important to get the clock offset from a device 

**Sixth Param** 

`(void *)&handler`

- this is the "Allow_role_switch" to a pointer variable called handler which is inited in like 258
- what allow_role_switch does it lets the other device to change to master or servent during active comms 
- this will most likely change since if the var `handler`  changes to 0 it would be able to switch 
but if it changes to 1 it will all for the possibliltiy to change 
- **NOTE** is a role switch happends, then the switch could disrupt the connection 

**Seventh Param** 

- 25000 is the microseconds for the max amount of time the function will wait before it returns an error 


#### hci_read_remote_name()

- this is mainly used to get the user friendly device name from the other device !

#### rfcomm_read function 

- this takes in 2 arguments, first is teh file stream and the scond being a string 
```c
char *rfcomm_read(FILE *fp, char *send) {
```

- It then inits the variables found in the fucntion
    - but the thing is that the `line` variable is a pointer to a bffer that will be 
    to store lines read from the file stream in this case the file pointer from earlier

- In this case line is set to 0x00 which defines the start of the buffer

**THIS IS ALL FOR IF STATEMENTS!** 

- an if statment only executes if the value inside the parenthesis is NOT ZERO 
    - IF IT IS ZERO IT WILL NOT EXECUTE !!!!!!!!!1
- here is an example; 

```c
if (1){
printf("hello goose\n");
}
```
The purpose of the final return statement being 0x00 (which is equivalent to the NULL pointer) is to 
indicate that no line of text was found that matched the condition specified by the if 
statements inside the while loop.

If the if condition inside the loop is never satisfied, the loop continues to execute until the end of 
the file is reached or some other error occurs. Once the end of the file is reached, the getline() 
function returns -1, indicating that there is no more input to read. At this point, the loop terminates, 
and the final return statement is executed, returning 0x00 (i.e., NULL) to indicate that no matching line was found.

Returning NULL in this case is a common convention in C programming. When a function returns a pointer 
type, NULL is often used to indicate that the function was not able to successfully perform its intended operation.

#### rfcomm_dev_req STRUCT 

- This is used to store alot of information for the bluetooth device foro communications 
- here is how the struct looks like: 

```c 
struct rfcomm_dev_req {
	int16_t		dev_id;
	uint32_t	flags;
	bdaddr_t	src;
	bdaddr_t	dst;
	uint8_t	channel;
};
```
- as you can see this takes the device id, the flags used, the source, destination, and channel

#### hci_get_route function 

- this is found in the hci lib header file 
- this is used to get the information about the device identifer 


#### I need some help with termios 
- this is the portion of the vidoe where i ask the sponsor what to 





#### What is device and where is it inited 

- device is inited in bt_rfcomm fucntion in bsnarf
    - the specific fucntion would be the `int rw_cmd(FILE *fd, struct opt options)` 

## How to get SMS messages in bluesnarf.c !!!

- All this information was found in the `rw_cmd()` function in the program 

- For this program to read the contents of the phones phone book 
    - This achieved through this command being ran on in the phonebook 
    - `snprintf(buffer, 32, "AT+CPBR=%d\r\n", options.N_MIN)`
- What the function does is it iterates through the range provided by the user N_MIN and N_MAX 

**Therefore** 

- this can also be accomplished through SMS as well

- These commands being enetered are called AT commands that can do various things with the information 
on a cell phone 

- For instance, to read all the recieved and un read messages in the device through this command 
    - We would to set the modem of the device to text mode which was already done earlier in the function, 
    - Then we can run this command `AT+CMGL="REC UNREAD"` or `AT+CMGL="REC READ"`
- These commands print out all the messages on the phone to the user.
- In addition there are also capabilities to send SMS messages as well!

> **NOTE: all this information was found in this webiste:** 

- https://m2msupport.net/m2msupport/sms-at-commands/#readsms


#### 2023-03-14

I have made a lot of progress when i comes to stealing SMS messages from a device 

- all that is left is to test the program 
- To do this you need to establish a bt connection with the device first 
- Then you need to disconnect them and run the bluensarfing program with this command: 
    - `sudo ./bluesnarfer -b 7C:38:AD:3D:5A:EF -C 2 -i` 
    - Here you would need to change the mac address of the device to the one you need to! 

#### The six types of Message storage areas 

> **All this can be found here: https://www.developershome.com/sms/cpmsCommand.asp**




- SM. It refers to the message storage area on the SIM card.

- ME. It refers to the message storage area on the GSM/GPRS modem or mobile phone. 
Usually its storage space is larger than that of the message storage area on the SIM card.

- MT. It refers to all message storage areas associated with the GSM/GPRS modem or mobile phone. 
For example, suppose a mobile phone can access two message storage areas: "SM" and "ME". The "MT" 
message storage area refers to the "SM" message storage area and the "ME" message storage area combined together.

- BM. It refers to the broadcast message storage area. It is used to store cell broadcast messages.
- SR. It refers to the status report message storage area. It is used to store status reports.
- TA. It refers to the terminal adaptor message storage area.

- all the information saved in the pointer is then set to the parse function ! 



#### Here is an important picture!!!! 

- i am currently trying to find a way to easily pair to a device with the reapsbery pi 
the thing is i need a pass key and say yes to irt all the time now i wanna see if there is a way
to accept the passkey without having to say yes 
the best way to do this is to use this command:

```bash
sudo hciconfig hci0 piscan
```




















