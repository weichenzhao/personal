from ctypes import *
from dpkt.ethernet import Ethernet
#import dpkt

# define the interface
read_pkt = cdll.LoadLibrary('./read_one_pkt.so')
# create a pointer
ret = c_void_p()
# pass this pointer
ret=read_pkt.read_pkt()
#print read_pkt.read_pkt.restype
#print "pkt len: ", ord(string_at(ret, 1))

# in returned string pointer
# the first byte is the number of
# pkt transfered
num=ord(string_at(ret, 1))
# get packet data
pkt=string_at(ret+1, num)

# parse using dpkt
parsed = Ethernet(pkt)

print parsed.src.encode('string-escape')
print parsed.dst.encode('string-escape')
print parsed.type
