## Capturing Bluetooth Traffic with Wireshark

Wireshark is commonly used to capture packets and contain them in a .pcap file for analysis. In our case, we will analyze the data captured by processing the hex values  into strings from Bluetooth packets to check for device names, protocols, and even plaintext messages to identify the nature of the packets. This will allow us to conceptualize and constuct both malicious and migitation methods for this project.

> **NOTE: This repository automates the process described above by checking for .pcap files and streamlining the process of processing the hex values and storing results

1. Create a directory to store script, .pcap file, and output file. I simply named mine "WiresharkAnalysis". Keep it empty for now and cd into it. 

```bash
mkdir WiresharkAnalysis
cd WiresharkAnalysis
```
3. Within the created directory, install the shell script. **Please ensure that you are either using Kali Linux or have Wireshark installed on your host device**.

```bash
wget https://github.com/joshuar49/EvilSmurf2/raw/main/DBD_Code/Wireshark/streamline.sh
```
3. Make the shell script (streamline.sh file) executable by changing using the chmod command

```bash
chmod -x streamline.sh
```
