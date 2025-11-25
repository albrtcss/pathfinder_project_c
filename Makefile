CC = gcc
CFLAGS = -Iinclude -std=c11 -Wall -Wextra
BUILD = build

SRC_GRID = src/grid.c
SRC_BFS = src/bfs.c
SRC_BFS_RUN = src/run_bfs.c
SRC_ASTAR = src/astar.c
SRC_ASTAR_RUN = src/run_astar.c
SRC_VIS_SIMPLE = src/visualize_simple.c
SRC_VIS_NCURSE = src/visualize_ncurses.c

all: run_bfs run_astar

$(BUILD):
	mkdir -p $(BUILD)

# build BFS runner
run_bfs: $(BUILD)
	$(CC) $(CFLAGS) -o $(BUILD)/run_bfs $(SRC_GRID) $(SRC_BFS) $(SRC_BFS_RUN)

# build A* runner
run_astar: $(BUILD)
	$(CC) $(CFLAGS) -o $(BUILD)/run_astar $(SRC_GRID) $(SRC_ASTAR) $(SRC_ASTAR_RUN)

# build simple visualizer (uses run_astar as main so it executes A* then calls animate)
visual_simple: $(BUILD)
	$(CC) $(CFLAGS) -o $(BUILD)/visual_simple $(SRC_GRID) $(SRC_ASTAR) $(SRC_ASTAR_RUN) $(SRC_VIS_SIMPLE)

# build ncurses visualizer (requires ncurses libs)
visual_ncurses: $(BUILD)
	gcc -Iinclude -std=c11 -Wall -Wextra \
	src/grid.c src/bfs.c src/astar.c \
	visual/visualize_ncurses.c src/run_ncurses.c \
	-lncursesw \
	-o build/visual_ncurses


# convenience: build everything
all: run_bfs run_astar visual_simple

run_all: run_bfs run_astar visual_simple
	@echo "Running run_all..."
	./build/run_bfs
	./build/run_astar
	./build/visual_simple

clean:
	rm -rf $(BUILD) results

.PHONY: all run_bfs run_astar visual_simple visual_ncurses run_all clean
