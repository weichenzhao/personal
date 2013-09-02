CC = gcc
CFLAGS = ../csapp.h ../csapp.c echoserver.c -o echoserver
TARGET = echoserverp

$(TARGET):$(OBJS)
	$(CC) ../csapp.c echoserverp.c -o echoserverp
	$(CC) ../csapp.c echoclient.c -o echoclient
clean:
	rm echoserverp echoclient
