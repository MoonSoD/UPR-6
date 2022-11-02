CC=gcc
CFLAGS=-pedantic -Wall -Werror --std=c99
OUT=main

.PHONY: all run clean

main: main.c
	$(CC) -o main main.c $(CFLAGS)

clean:
	@rm $(OUT)
