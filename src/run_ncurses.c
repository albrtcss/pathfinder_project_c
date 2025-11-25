#include <stdio.h>
#include <stdlib.h>
#include "../include/grid.h"
#include "../include/bfs.h"
#include "../include/visualize_ncurses.h"


int main() {
    Grid *g = grid_create_from_file("maps/map1.txt");
    if (!g) {
        printf("Failed to load map!\n");
        return 1;
    }

    int sr, sc, gr, gc;
    if (grid_find_start_goal(g, &sr, &sc, &gr, &gc) != 0) {
        printf("Start/Goal not found!\n");
        return 1;
    }

    Node path[2048];
    int path_len = 0;

    if (bfs(g, sr, sc, gr, gc, path, &path_len) == 0) {
        visualize_ncurses(g, path, path_len);
    } else {
        printf("Path not found.\n");
    }

    grid_destroy(g);
    return 0;
}
