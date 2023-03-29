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


























