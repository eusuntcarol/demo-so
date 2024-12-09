CC=gcc
CFLAGS=-g
LDLIBS=-lpthread

all: fifo_reader fifo_writer client server

fifo_reader: fifo_reader.o
fifo_reader.o: fifo_reader.c

fifo_writer: fifo_writer.o
fifo_writer.o: fifo_writer.c

server: server.o
server.o: server.c

client: client.o
client.o: client.c

clean:
	rm -f fifo_reader fifo_writer client server *.o
