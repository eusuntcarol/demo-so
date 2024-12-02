CC=gcc
CFLAGS=-g
LDLIBS=-lpthread

all: dups pipe pipe_redirect

dups: dups.o
dups.o: dups.c

pipe: pipe.o
pipe.o: pipe.c

pipe_redirect: pipe_redirect.o
pipe_redirect.o: pipe_redirect.c

clean:
	rm -f dups pipe pipe_redirect *.o
