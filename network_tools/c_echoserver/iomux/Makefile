CC = gcc
CFLAGS = ../csapp.h ../csapp.c echoserver.c -o echoserver
TARGET = echoserverp

$(TARGET):$(OBJS)
	$(CC) ../csapp.c echoserveri.c -o echoserveri
	$(CC) ../csapp.c echoclient.c -o echoclient
	$(CC) ../csapp.c 1_cmdline.c -o cmd_only
clean:
	rm cmd_only echoserveri echoclient
