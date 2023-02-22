## Capturing Bluetooth Traffic with Wireshark

Wireshark is commonly used to capture packets and contain them in a .pcap file for analysis. In our case, we will analyze the data captured by processing the hex values  into strings from Bluetooth packets to check for device names, protocols, and even plaintext messages to identify the nature of the packets. This will allow us to conceptualize and constuct both malicious and migitation methods for this project.

> NOTE: This repository automates the process described above by checking for .pcap files and streamlining the process of processing the hex values and storing results

### Configuration 

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

![image](https://user-images.githubusercontent.com/107435186/220528273-04fc0fc4-c550-4603-b3a2-ac919eb8e262.png)

> NOTE: packets.pcap is the default name of the file the shell script is looking for. You may change the name in ```bash streamline.sh``` by opening the script in your preferred text editor and manually changing the name, but make sure it matches the one you assign to the saved Wireshark file!

6. If you are looking for or expecting a specific string in the processed hex values, uncomment the grep command found in ```streamline.sh``` and replace the "hello" value with a value of your choice, as the instructions indicate.

![image](https://user-images.githubusercontent.com/107435186/220528640-67ada54c-768e-4bc6-ba68-5e33d7d7c79c.png)

7. The default time that the shell scrip refreshes to check for the file is 120 seconds, or 2 minutes. This may be changed to the user's preference by replacing the value next to the ```sleep``` command (the recommended time being the length that the user spends saving the previous files, then running and saving another Wireshark file).

### Execution

8. Run the shell script

```bash
./streamline.sh
```

9. Ensure that the strings are found in the ```output.txt``` file and the ```filter.txt``` file (if you've enabled the grep command). You will also be given an confirmation of the Wireshark file's existence in the terminal, or a notice otherwise.

- Execution of shell script and resulting files

![image](https://user-images.githubusercontent.com/107435186/220529104-8a66cd59-25df-437c-99a5-c6029f2fba54.png)

- All outputs

![image](https://user-images.githubusercontent.com/107435186/220529246-5f232ffa-40f3-410d-9165-53fd478add03.png)

- Filtered output

![image](https://user-images.githubusercontent.com/107435186/220529330-2564fb73-daa7-4cfa-9c24-34d791f116b8.png)

