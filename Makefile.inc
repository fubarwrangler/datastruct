CC = gcc
CFLAGS = -g -Wall
OBJ = $(SRC:.c=.o)
INCFLAGS = ../include/
LDFLAGS = -Wl,-rpath,/usr/local/lib
LIBS =

count:
	wc *.c

.PHONY: count
