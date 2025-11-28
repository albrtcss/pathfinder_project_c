CC = gcc
CFLAGS = -Iinclude -std=c11 -Wall -Wextra
BUILD = build

SRC_GRID = src/grid.c
SRC_ASTAR = src/astar.c
SRC_BFS = src/bfs.c

SRC_VIS_SIMPLE = visual/visualize_simple.c
SRC_VIS_NCURSE = visual/visualize_ncurses.c

SRC_RUN_VIS_SIMPLE = src/run_visual_simple.c
SRC_RUN_VIS_NCURSE = src/run_ncurses.c

all: visual_simple

$(BUILD):
	mkdir -p $(BUILD)

visual_simple: $(BUILD)
	$(CC) $(CFLAGS) -o $(BUILD)/visual_simple \
	$(SRC_GRID) $(SRC_ASTAR) $(SRC_VIS_SIMPLE) $(SRC_RUN_VIS_SIMPLE)

visual_ncurses: $(BUILD)
	gcc -Iinclude -std=c11 -Wall -Wextra \
		src/grid.c src/astar.c \
		visual/visualize_ncurses.c src/run_ncurses.c \
		-I/mingw64/include \
		-L/mingw64/lib -lpdcurses \
		-o build/visual_ncurses


.PHONY: all visual_simple visual_ncurses clean

clean:
	rm -rf $(BUILD) results
