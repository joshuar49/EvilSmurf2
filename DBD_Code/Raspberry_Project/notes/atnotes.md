# This is going to be all the notes that I have taken about SMS and PDU 

- SMS can be sent to a phone even if it is offline the phone will recieve it 
once the other phone has gotten a connection 

- SMS is 100 supported by GSM mobile phonese 
- Youyc an also send messasges to various different carries with SMS 

- The can carry binary data which means you can use it to send ringtones, pics, operator logos, 
wall papers, animations Vcards and so on 

- supports billing so that payments can be made 

#### Email, fax, and voice message notifications

- once an email gets sent a user can then send a text once the email arrives to teh system 

#### Remote Sys Monitorign 

- send sms for system monitoring 

## What is an SMS Center? SMSC 

**The SMS center** is responisible for handling SMS operationsk of a wireless network 
- when a SMS message is sent froma mobile phone ti will reach a SMS center first!!! 
- The SMS center will then forward the SMS to the destination 
    - it is used to route SMS and regulate the process 
    - this is where the message is stored if a device is switched off the message will stay in the SMS center 
    - then the SMS center will forward teh message once the device is available 

- it is possible that once can use a third party SMSC located outside teh network system 

> **YOU MUST KNOW THE ADDRESS OF THE WIRELESS NETWORKS SMSC TO USE SMS WITH MOBILE PHONE**
- this is mainly like a normal phone number and is often preset in the SIM card 

## Basic Concpets of SMS tech

#### Validaity period of a sms message 

- sms is temp stored in the sms center if phone offline, 
- you can specify a time in which the message can be deleted from the SMS center this is called a 
**vailidity periord**

#### Message Status Report 

sometimes you wanna know if the message reched the recipents phone 
- to get this information you need to set a flag in the SMS message to tell the SMS center you want a delievery of 
the message 
- This feature is automatically turned off in GSM GPRS modems 

#### Message Submission Reports 
 
once the message is sent from the phone to teh SMSC the center will send back a submission report to the mobile phone if there 
were any errors 
- there might not even be a report to tell why the message has failed 
- no report for a while means the message was lost for a while 

#### Message Delivery Reports 

- after getting a message the phone will sned back a message delivery report to the SMS center to inform that 
if there are any errors  

## Intra operator SMS Messages 

If **BOTH** you and a friend are using the the mobile service of the same network operator, then you guys will 
only be involved in only one wireless net op 
- this is called **intra operators** 

#### Transmission Process of Intra messages 






#### I left off on less 5 if im not wrong starting number 10 

## How to send SMS messages from a computer / pc 

There are 2 ways of sending a message from a cell phone 

1. Connect to a mobile phone or GSM GPRS modem to a computer 
- then you would would use the comptuer to and AT commands to the phoine and tell it to send messages 

in theory what i can do is send sms messages to devices or even make the other device send messages tha device 
with a GSM modem 

2. connect the computer to a SMS center ot SMS gateway of a wireless carrier, then send SMS messages 
- this is done using protocols supported by the message center 

To send sms messages you would need to place a valid SIM card from a wireless carrier into a phone or modem 
which is then connect to a computer 

**There are multiple ways to connect to the modem** 
- serial cable 
- USB cable 
- bluetooth link 
- infra red link 

| AT command   | Meaning    |
|--------------- | --------------- |
| AT+CMGS   | Send Message   |
| AT+CMSS   | Send message from storage   |
| AT+CMGW   | Write message to memory   |
| AT+CMGD   | Delete Message   |
| AT+CMGC   | Send command |
| AT+CMMS   | More messages to send |

#### there is a major draw back to sending SMS messages through a mobile phone 

This woul dbe the low SMS sending rate 

- Only 6 - 10 SMSM messages can be sent perminute 
- Performance is not affected by the connection type the same out put will be done through the use of 
bluetooth or cable connections 
- The determining factor would be the wireless network 

#### Skipping 10.2 10.2.2 


#### 25.5 Syntax of AT CMGS with PDU mode 


Here is the syntax of CMGS: 

```bash
+CMGS=TPDU_length<CR>SMSC_number_and_TPDU<Ctrl+z>
```

This will be a real example of how the message will look like: 

```bash
AT+CMGS=42<CR>07915892000000F001000B915892214365F7000021493A283D0795C3F33C88FE06CDCB6E32885EC6D341EDF27C1E3E97E72E<Ctrl+z>
```

It is divided into two main parts 

**TPDU_Length Param** 
This specifies the length in octets which is 8bits of the TPDU (Transfer protocol data unit) assigned to the 
SMSC number adn TPDU param 

in the previous example we assigned that the SMSC number and TPDU param is: 

`01000B915892214365F7000021493A283D0795C3F33C88FE06CDCB6E32885EC6D341EDF27C1E3E97E72E` 

**TPDU** in encoded in hexadecimal format in this case there are 84 character which means that there are 42 octets so the length is 
42 this is done by dividing the amount of characters in half





- Once you are done with entering values in CMGS you need to end it with <crtl+z>

**Focusing on the whole value:**

- 07915892000000F001000B915892214365F7000021493A283D0795C3F33C88FE06CDCB6E32885EC6D341EDF27C1E3E97E72E

Here is the value that we will be focusing more on 
- This value can be divided into 2 main parts

1. The first part of the string contains information about the SMSC that will be used to send the SMS message: 
- 07915892000000F0 

2. The second part is the TPDU 
- 01000B915892214365F7000021493A283D0795C3F33C88FE06CDCB6E32885EC6D341EDF27C1E3E97E72E 
- This is the lenght part that we talked about in the previosu example 

**More on SMSC** 

This part can be further broken down into three different parts 

- 07915892000000F0 
- 07 91 5892000000F0 

**First Sub Field: Lenght of Second and Third Sub Fields**

This sub section specifies the length in octets, for instance without the 07 there are 14 hexadecimal digits in `915892000000F0`
- Each represents 4 bits so they are 7 octets in length which is why the first field is 0x07 

**Second Sub Field: Type of SMSC number**

This portion focuses on what type of number the thrid portion of the numbewr is 
- In this case this is the 91 portion that was divided earlier 
- There are 2 values that are commonly used in the second param to send messages 

- `81` and `91` 

**81** 

81 means that the SMSC number if formated using the typical ISDN telephony numbering plan (ITU E.164/E.163)
- But this is not sure if its international or national 
- For instance if the number of the SMSC number is `85290000000` and the second number is 81 then the value can eiter one of 2 things 

1. 85290000000 with contry code included or 
2. 90000000 with contry code omitted 

**91** 

91 means that the number is formatted using typical ISDN and is an internation number 
Assuming that the number for SMSC is the same: 85290000000 then the value is going to still be 85290000000

**Third subfield SMSC Number** 

This is going to be the actual SMSC number that will be used, in tis case 0x5892000000F0 represents the number 85290000000

**Here is how the number is derived:**

1. Starting from the left we need to group te digits in PAIRS so 85290000000 will be: 
- 85 29 00 00 00 0 

2. The last pair only has a single digit which menas that we need to add the F character to make up the pair 
Therefore the new pair will look like this: 85 29 00 00 00 0F 

3. Then we need to swap the pairs so that we cna use them to look like this: 

`58 92 00 00 00 F0` 

> **NOTE: it is possible for the modem to use the SMSC number by using the command:**

`AT+CSCA` this is the Service Centre Address 


**The TPDI Part** 

This is the part can be divided into 9 different parts like this: 

- 01 00 0B 91 5892214365F7 00 00 21 493A283D0795C3F33C88FE06CDCB6E32885EC6D341EDF27C1E3E97E72E

**The first Sub field** 
The first subfield of the modem os phone tells the modem alot of things such as 

- type of the TPDU 
- if the SMSC should reject duplicate TPDU 
- if validity period exists in TPDU and the format of the validity period if it exists 
- if the reply path is requested 
- if a user data header exists in the TPDU 
- if the status report is requested from the SMSC 

**A value of 0x01 means:** 
- the type of TPDU is sms submit 
- the SMSC should not reject duplicate TPDU 
- No validity period exists on TPDU
- no reply path is required 
- no user data header exits in TPDU 
- no status report is requested from teh SMSC 

**The second sub field: Message Reference Number**

The message referenece number can be an integer of either 0 to 255 
- the value of 0x00 tells the modem to assign a message reference number to the SMS message automatically 

**Third Sub Field: Length of the Desintation Phone Number**

This portion of the TPDU specifies the length in digits of the destination phone number

- in this case the phone number is 85291234567 which is 11 digits long, therefore the thrid subfield will ned to be 
-`0x0b` which is 11 in decimal 

**Fourth Sub Field: Type of the Destination phone number**

- these values can be either 81 or 91 as mentioned previously 

**Fifth Sub Field: Desintation Phone Number** 

This specifies the phone number that will be used in this case the value of: `0x5892214365F7` 
is represented by the value of : 85291234567 

- this is done in the same way that we did before which is like this: 

1. making everything into pairs: 

85 29 12 34 56 7 

2. since there is a number that doesnt have a pair we need to add the character `F` to the end of that number to make it a pair 
- like this: `7F` 

3. Lastly we need to swap the digits of each pair !

58 92 21 43 65 F7 will be the new pair and final translation of the destination phone number!

**Sixth Sub Field: Protocol ID** 

This is the protocl id which most time the value should be 0x00 for most caases 

**Seventh Sub Field: Data Coding Scheme** 

With the use of 0x00 we are telling the modem that the test in the SMS is encoded according to GSM 7 but default 

**Eight Sub Field: Length of the SMS message body** 

This field is in charge of sending the length of the SMS message body in septets which is 7 bits 
The value of 0x21 means that there are 33 septets (These are characters that are represented by 7 bit according to the GMS 7 bit )

**Ninth Sub Field: SMS Message Body** 

The current value of the message body is this: `0x493A283D0795C3F33C88FE06CDCB6E32885EC6D341EDF27C1E3E97E72E`

- This message is "It is easy to send text messages" and below we will cover how this message has been translated to this: 

- `49 74 20 69 73 20 65 61 73 79 20 74 6F 20 73 65 6E 64 20 74 65 78 74 20 6D 65 73 73 61 67 65 73 2E` 

Since this is encoded as a 7 bit there is a bit that is wasted in every octet. To prevent this from
happening SMS specifications require to pack 7 but characters in octetes 

**Packing Process**


The binary representation of the first character is 1001001. The most significant bit of the first oct is unused we will fill 
it with the least significant bit of the second character which in this case is zero 

- Therefore the 


## Format of the info response of the AT CMGS command in SMS PDU mode 

**We need to instruct the modem to operate sms in PDU mode** 

First we need to send out the command: `AT+CMGF=0` so that we can tell the modem how to 

**Setting the optional SMSC number so that we can send text messages** 
Second, this is optional but we can set the SMSC number to be used to send SMS text messages 

This is done through the use of this command: `AT+CSCA`  but this isnt needed since in PDU mode 
once we write the message we dont need to specify the number 


**Sending Text Messages**

my message center is 12063130004














