CC=gcc
CFLAGS=-g
LDLIBS=-lpthread

all: fork fork2 exec my_server vphys my_worker_node

fork: fork.o

fork.o: fork.c

fork2: fork2.o

fork2.o: fork2.c

vphys: vphys.o

vphys.o: vphys.c

exec: exec.o

exec.o: exec.c

my_server: my_server.o

my_server.o: my_server.c

my_worker_node: my_worker_node.o

my_worker_node.o: my_worker_node.c

clean:
	rm -f fork fork2 vphys exec my_server my_worker_node *.o
