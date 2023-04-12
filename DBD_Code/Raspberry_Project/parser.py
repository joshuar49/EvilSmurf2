file_name = input("Enter your output file to clean here with the file extension: ")
with open(file_name, 'r') as file:
    for line in file:
        if line.startswith('Response From Device:'):
            line.strip("\n")
            text = line.strip('Response From Device:').strip() 
            if text:
                print(f'Response From Device: {text}')
        else:
            print(line.strip("\n"))

