#include <stdio.h>
#include "../include/grid.h"

int main() {
    Grid* g = grid_create_from_file("maps/map1.txt");

    printf("Map loaded:\n");
    grid_print(g);

    int sr, sc, gr, gc;
    grid_find_start_goal(g, &sr, &sc, &gr, &gc);

    printf("Start: (%d,%d)\n", sr, sc);
    printf("Goal:  (%d,%d)\n", gr, gc);

    grid_destroy(g);
    return 0;
}
