CC = gcc
CFLAGS = -Iinclude -std=c11 -Wall -Wextra
BUILD = build

SRC_GRID = src/grid.c
SRC_BFS = src/bfs.c
SRC_BFS_RUN = src/run_bfs.c
SRC_ASTAR = src/astar.c
SRC_ASTAR_RUN = src/run_astar.c

# lokasi yang benar setelah dipindah
SRC_VIS_SIMPLE = visual/visualize_simple.c
SRC_VIS_NCURSE = visual/visualize_ncurses.c

all: run_bfs run_astar

$(BUILD):
	mkdir -p $(BUILD)

run_bfs: $(BUILD)
	$(CC) $(CFLAGS) -o $(BUILD)/run_bfs $(SRC_GRID) $(SRC_BFS) $(SRC_BFS_RUN)

run_astar: $(BUILD)
	$(CC) $(CFLAGS) -o $(BUILD)/run_astar $(SRC_GRID) $(SRC_ASTAR) $(SRC_ASTAR_RUN)

visual_simple: $(BUILD)
	$(CC) $(CFLAGS) -o $(BUILD)/visual_simple \
		$(SRC_GRID) $(SRC_ASTAR) $(SRC_ASTAR_RUN) $(SRC_VIS_SIMPLE)

visual_ncurses: $(BUILD)
	gcc -Iinclude -std=c11 -Wall -Wextra \
		src/grid.c src/bfs.c src/astar.c \
		$(SRC_VIS_NCURSE) src/run_ncurses.c \
		-lncursesw \
		-o build/visual_ncurses

visual_sdl: $(BUILD)
	gcc -Iinclude -std=c11 -Wall -Wextra \
		src/grid.c src/bfs.c src/bfs_visual.c src/astar.c \
		gui/visualize_sdl.c src/run_sdl.c \
		-lSDL2 \
		-o build/visual_sdl

clean:
	rm -rf $(BUILD) results

.PHONY: all run_bfs run_astar visual_simple visual_ncurses visual_sdl run_all clean
