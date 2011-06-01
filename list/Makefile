CC = gcc
CFLAGS = -g -Wall
SRC = sllist.c dllist.c
OBJ = $(SRC:.c=.o)
INCFLAGS = ../include/
LDFLAGS = -Wl,-rpath,/usr/local/lib
LIBS =

all: $(OBJ)

#.SUFFIXES:
#.SUFFIXES:	.c .cc .C .cpp .o

count:
	wc *.c *.C *.cpp *.h

clean:
	rm -f *.o *.a *.so

%.o: %.c
	$(CC) $(CFLAGS) -I $(INCFLAGS) -fpic -c $? -o $@

.PHONY: all
.PHONY: count
.PHONY: clean
