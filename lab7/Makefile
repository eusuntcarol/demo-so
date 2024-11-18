CC=gcc
CFLAGS=-g
LDLIBS=-lpthread

all: fork fork2 exec my_app vphys

fork: fork.o

fork.o: fork.c

fork2: fork2.o

fork2.o: fork2.c

vphys: vphys.o

vphys.o: vphys.c

exec: exec.o

exec.o: exec.c

my_app: my_app.o

my_app.o: my_app.c

clean:
	rm -f fork fork2 vphys exec my_app *.o
