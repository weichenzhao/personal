CC = gcc-4.9
CFLAGS = -Wall -g ../csapp.h ../csapp.c 
TARGET = echoserver

$(TARGET):$(OBJS)
	$(CC) $(CFLAGS) echoserver.c -o echoserver
	$(CC) $(CFLAGS) echoclient.c -o echoclient
clean:
	rm echoserver echoclient
