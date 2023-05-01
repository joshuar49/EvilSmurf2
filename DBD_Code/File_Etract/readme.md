# Bluetooth File Extraction Program
- This directory will contin all the files for extracting a file using bluetooth!
- In able to run the Bluetooth File extraction Program a Server device, (Victim/Rasberry Pi) , and a Client device, (Adversary/Virtual Machine), is needed.
> **NOTE: To be able to successfully incorporate fileextraction is is important to run the server code on the victim device, prior to running the fileextraction.c code**
- First step is to compile the server program within the server device
```bash 
gcc -o server fe_server.c -libbluetooth
```
- Afterwards we need to utilize the Client device, (Adversary/Virtual Machine), to then compile the client program
```bash 
gcc -o client fileextraction.c -libbluetooth 
```
- Once this is done, we then run the comipled server program on the server device and then follow up with running the file extraction code on the client device to then extract the file
```bash 
./server 
```
```bash 
./client 
```




