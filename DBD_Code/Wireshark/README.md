## Capturing Bluetooth Traffic with Wireshark

Wireshark is commonly used to capture packets and contain them in a .pcap file for analysis. In our case, we will analyze the data captured by processing the hex values  into strings from Bluetooth packets to check for device names, protocols, and even plaintext messages to identify the nature of the packets. This will allow us to conceptualize and constuct both malicious and migitation methods for this project.

> NOTE: This repository automates the process described above by checking for .pcap files and streamlining the process of processing the hex values and storing results

1. Create a directory to store script, .pcap file, and output file. I simply named mine ```WiresharkAnalysis```. Keep it empty for now and cd into it. 

```bash
mkdir WiresharkAnalysis
cd WiresharkAnalysis
```
3. Within the created directory, install the shell script. **Please ensure that you are either using Kali Linux or have Wireshark installed on your host device**.

```bash
wget https://github.com/joshuar49/EvilSmurf2/raw/main/DBD_Code/Wireshark/streamline.sh
```
4. Make the shell script (streamline.sh file) executable by changing using the chmod command

```bash
chmod -x streamline.sh
```
5. Next, open your Wireshark application and run a scan on devices exchanging Bluetooth packets. Save the file as ```packets.pcap``` in the ```WiresharkAnalysis``` directory.

> NOTE: packets.pcap is the default name of the file the shell script is looking for. You may change the name in ```bash streamline.sh``` by opening the script in your preferred text editor and manually changing the name, but make sure it matches the one you assign to the saved Wireshark file!

6. If you are looking for or expecting a specific string in the processed hex values, uncomment the grep command found in ```streamline.sh``` and replace the STRING value with a value of your choice, as the instructions indicate.

7. Run the shell script

```bash
./streamline.sh
```

8. Ensure that the strings are found in the ```output.txt``` file and the ```filter.txt``` file (if you've enabled the grep command). You will also be given an confirmation of the Wireshark file's existence in the terminal, or a notice otherwise.
