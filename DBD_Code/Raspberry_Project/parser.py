from gsmmodem.pdu import decodeSmsPdu

file_name = input("Enter your output file to clean here with the file extension: ")
with open(file_name, 'r') as file:
    for line in file:
        if line.startswith('Response From Device:'):
            line.strip("\n")
            index = len("Response From Device: ")
            text = line.strip('Response From Device:').strip()
            if text:
                if text != "OK" and not text.startswith("+CMGL"):
                    str(text)
                    print(decodeSmsPdu(text))
                else:
                    print(f'Response From Device: {text}')
        else:
            print(line.strip("\n"))


#mess = input("Enter your pdu messaer here and hopefully we will see what happens: ")

#print(decodeSmsPdu("00040B917130161876F00000321013218121610AD9771D242ED3E96539"))
