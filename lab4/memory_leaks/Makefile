CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
SOURCES = $(wildcard *.c)
TARGETS = $(SOURCES:.c=)

all: $(TARGETS)

ex%: ex%.c  
	$(CC) $(CFLAGS) -o $@ -lm $<

.PHONY: clean
clean:
	rm -f $(TARGETS)
