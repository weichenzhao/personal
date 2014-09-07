import socket
import time

UDP_IP = "10.1.2.3"
UDP_PORT = 5005

sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
sock.bind((UDP_IP, UDP_PORT))

count = 0
first = 1
for i in range(100000):
    data, addr = sock.recvfrom(1024) # buffer size is 1024 bytes
    if first:
        start = time.time()
        first = 0
    count += len(data)
    #print "received message:", data
end = time.time()
print "time: ", end - start
print "data: ", count , "bytes"
print "rate: ", (count * 1.0 / 1024) / (end - start), "KBps"
print "rate: ", (count * 8.0 / 1024) / (end - start), "Kbps"
