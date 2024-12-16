CC=gcc
CFLAGS=-g
LDLIBS=-lpthread

all: client server

server: server.o
server.o: server.c

client: client.o
client.o: client.c

clean:
	rm -f client server *.o
