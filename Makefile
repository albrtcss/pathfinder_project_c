CC = gcc
CFLAGS = -Iinclude -std=c11 -Wall -Wextra

all: run

run: build/run_example

build/run_example: src/grid.c src/run_example.c
	mkdir -p build
	$(CC) $(CFLAGS) -o build/run_example src/grid.c src/run_example.c

clean:
	rm -rf build
