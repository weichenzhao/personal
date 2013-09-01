CC = gcc
CFLAGS = ../csapp.h ../csapp.c echoserver.c -o echoserver
TARGET = echoserver

$(TARGET):$(OBJS)
	$(CC) ../csapp.c echoserver.c -o echoserver
	$(CC) ../csapp.c echoclient.c -o echoclient
clean:
	rm echoserver echoclient
