SRC = sllist.c dllist.c

include ../Makefile.inc

all: liblist.a

%.o: %.c
	$(CC) $(CFLAGS) -I $(INCFLAGS) -fpic -c $? -o $@

liblist.a: $(wildcard *.o)
	$(AR) rcs liblist.a *.o

.PHONY: all
.PHONY: count
.PHONY: clean
