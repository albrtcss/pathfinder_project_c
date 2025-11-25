CC = gcc
CFLAGS = -Iinclude -std=c11 -Wall -Wextra
BUILD = build

SRC_BFS = src/grid.c src/bfs.c src/run_bfs.c
SRC_ASTAR = src/grid.c src/astar.c src/run_astar.c

all: run_bfs run_astar

$(BUILD):
	mkdir -p $(BUILD)

run_bfs: $(BUILD)
	$(CC) $(CFLAGS) -o $(BUILD)/run_bfs $(SRC_BFS)

run_astar: $(BUILD)
	$(CC) $(CFLAGS) -o $(BUILD)/run_astar $(SRC_ASTAR)

clean:
	rm -rf $(BUILD)/*
