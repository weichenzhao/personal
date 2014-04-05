from ctypes import *
from dpkt.ethernet import Ethernet
import time
#import dpkt

# define the interface
read_pkt = cdll.LoadLibrary('./read_one_pkt.so')
# create a pointer
ret = c_void_p()
table={}
ret = read_pkt.init()

while(True):
    # pass this pointer
    read_pkt.read_pkt(ret)

    #print read_pkt.read_pkt.restype
    #print "pkt len: ", ord(string_at(ret, 1))

    # in returned string pointer
    # the first byte is the number of
    # pkt transfered
    num=ord(string_at(ret, 1))
    
    if(num>0):
        # get packet data
        pkt=string_at(ret+1, num)

        # parse using dpkt
        parsed = Ethernet(pkt)
		
        key=parsed.src+parsed.dst#+parsed.data.src+parsed.data.dst
        key=key.encode('string-escape')
        if(key not in table):
            table[key]=1
        else:
            table[key]+=1
        print len(table.keys())
        print parsed.src.encode('string-escape') + parsed.dst.encode('string-escape')
        #print parsed.type
    #print ret
    if(ret == 0):
        exit
    #time.sleep(0.1)
read_pkt.freeme(ret)
