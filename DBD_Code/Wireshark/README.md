## Capturing Bluetooth Traffic with Wireshark

Wireshark is commonly used to capture packets and contain them in a .pcap file for analysis. In our case, we will analyze the data captured by processing the hex values  into strings from Bluetooth packets to check for device names, protocols, and even plaintext messages to identify the nature of the packets. This will allow us to conceptualize and constuct both malicious and migitation methods for this project.

> NOTE: This repository automates the process described above by checking for .pcap files and streamlining the process of processing the hex values and storing results

### Configuration 

1. Create a directory to store .pcap files after processing them. I named mine ```SavedPCAP```. Keep it empty
```bash
mkdir SavedPCAP
```
2. Create a directory to store the bash script, .pcap file (temporarily), and output files. I simply named mine ```WiresharkAnalysis```. Keep it empty for now and cd into it. 

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
5. Next, open your Wireshark application and run a scan on devices exchanging Bluetooth packets. Save the file with name of your choice in the ```WiresharkAnalysis``` directory.

> NOTE: The only naming convention that you MUST follow aside from the default for file names is to NOT include a space. 

![image](https://user-images.githubusercontent.com/107435186/220528273-04fc0fc4-c550-4603-b3a2-ac919eb8e262.png)

6. Configure the directory where your SavedPCAP is in the shell script (line 8). Replce "Directory" with your directory. This will ensure that the saved .pcap files will make their way to the correct folder

7. If you are looking for or expecting a specific string in the processed hex values, uncomment the grep command found in ```streamline.sh``` (line 10) and replace the "hello" value with a value of your choice, as the instructions indicate.

8. The default time that the shell scrip refreshes to check for the file is 120 seconds, or 2 minutes. This may be changed to the user's preference by replacing the value next to the ```sleep``` command (line 10). It is recommended to not make the time too short to save computing power.

![Wireshark3](https://user-images.githubusercontent.com/107435186/222220746-f2e386bf-4ea3-49a8-99de-8a7cd9623a3c.PNG)

### Execution

9. Run the shell script

```bash
./streamline.sh
```

10. Ensure that the strings are found in the ```output.txt``` file and the ```filter.txt``` file (if you've enabled the grep command). Also make sure the .pcap file is now in SavedPCAP instead of WiresharkAnalysis.

- WiresharkAnalysis Output

![Wireshark4](https://user-images.githubusercontent.com/107435186/222220941-5d2817c8-499d-4902-b882-eb9e539f0799.PNG)

- SavedPCAP Output

![Wireshark5](https://user-images.githubusercontent.com/107435186/222221022-076961bc-2e33-402e-b2c6-4db629584ae5.PNG)


