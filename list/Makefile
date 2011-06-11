
SRC = sllist.c dllist.c 

all: $(SRC) test

test: dllist.o
	$(CC) $(CFLAGS) -I $(INCFLAGS) dllist.o dllist_test.c -o dllist_test

%.o: %.c
	$(CC) $(CFLAGS) -I $(INCFLAGS) -fpic -c $? -o $@

include ../Makefile.inc
.PHONY: all
.PHONY: count
.PHONY: clean
