SRC = sllist.c dllist.c

include ../Makefile.inc

%.o: %.c
	$(CC) $(CFLAGS) -I $(INCFLAGS) -fpic -c $? -o $@

.PHONY: all
.PHONY: count
.PHONY: clean
