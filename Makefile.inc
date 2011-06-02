CC = gcc
CFLAGS = -g -Wall
OBJ = $(SRC:.c=.o)
INCFLAGS = ../include/
LDFLAGS = -Wl,-rpath,/usr/local/lib
LIBS =

all: $(OBJ)

#.SUFFIXES:
#.SUFFIXES:	.c .cc .C .cpp .o

count:
	wc *.c

clean:
	rm -f *.o *.a *.so


.PHONY: all
.PHONY: count
.PHONY: clean
