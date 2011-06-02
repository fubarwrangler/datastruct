SRC = sllist_test.c

include ../Makefile.inc

CFLAGS += -march=core2

%.o: %.c
	$(CC) $(CFLAGS) -I $(INCFLAGS) $? -o $@
