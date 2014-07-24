import socket
from scapy.all import *
import pdb
#soc=socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
#soc.bind(('',56789))
#soc.setsockopt(socket.SOL_SOCKET, socket.SO_NO_CHECK, 1)
rawudp=socket.socket(socket.AF_INET, socket.SOCK_RAW, socket.IPPROTO_UDP)
rawudp.bind(('0.0.0.0',56789))
rawudp.setsockopt(socket.SOL_IP, socket.IP_HDRINCL,1)
#pkt = IP(flags=2, id=0)/UDP(sport=56789, dport=7890)/'hello'
pkt = IP()/UDP(sport=56789, dport=7890)/'hello'
pdb.set_trace()
rawudp.sendto(pkt.build(), ('127.0.0.1',7890))
rawudp.sendto(pkt.build(), ('127.0.0.1',7890))
rawudp.sendto(pkt.build(), ('127.0.0.1',7890))
