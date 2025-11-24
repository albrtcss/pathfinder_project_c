CC = gcc
CFLAGS = -Iinclude -std=c11 -Wall -Wextra

SRC = src/grid.c src/bfs.c src/run_bfs.c
OUT = build/run_bfs

all: run_bfs

run_bfs:
	$(CC) $(CFLAGS) -o $(OUT) $(SRC)

clean:
	rm -f build/run_bfs
