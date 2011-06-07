SRC = sllist_test.c
CFLAGS = -Wall -march=core2
TESTS = sllist_test

all: $(TESTS)

sllist_test: sllist_test.c
	$(CC) $(CFLAGS) -I ../include $@.c ../list/liblist.a -o $@

clean:
	rm $(TESTS)
