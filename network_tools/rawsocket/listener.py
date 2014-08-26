import socket
so = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
so.bind(('',7890))
while True:
   print so.recv(1024)

