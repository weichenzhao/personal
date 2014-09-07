import socket

UDP_IP = "10.1.2.3"
UDP_PORT = 5005
MESSAGE = "Hello, World!" * 100

print "UDP target IP:", UDP_IP
print "UDP target port:", UDP_PORT
print "message:", MESSAGE

sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
for i in range(200000):
    sock.sendto(MESSAGE, (UDP_IP, UDP_PORT))
