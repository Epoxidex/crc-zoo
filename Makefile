CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -I include
SRC     = src/crc.c
TEST    = tests/test_crc.c

.PHONY: all test clean

all: test

test: $(SRC) $(TEST)
	$(CC) $(CFLAGS) $(SRC) $(TEST) -o test_crc
	./test_crc

clean:
	rm -f test_crc
