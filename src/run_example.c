// src/run_example.c
#include <stdio.h>
#include "../include/grid.h"

int main(void) {
    Grid *g = grid_create_from_file("maps/map2.txt");
    if (!g) { fprintf(stderr, "Failed to load map\n"); return 1; }
    printf("Map loaded\n");
    grid_print(g);
    int sr, sc, gr, gc;
    if (grid_find_start_goal(g, &sr, &sc, &gr, &gc) == 0) {
        printf("Start: (%d,%d) Goal: (%d,%d)\n", sr, sc, gr, gc);
    } else {
        printf("Start or Goal not found\n");
    }
    grid_destroy(g);
    return 0;
}
