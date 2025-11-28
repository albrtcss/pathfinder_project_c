#include <stdio.h>
#include <stdlib.h>
#include "../include/grid.h"
#include "../include/bfs.h"
#include "../include/visualize_sdl.h"

int main() {
    Grid *g = grid_create_from_file("maps/map1.txt");
    if (!g) {
        printf("Failed to load map.\n");
        return 1;
    }

    int sr, sc, gr, gc;
    if (grid_find_start_goal(g, &sr, &sc, &gr, &gc) != 0) {
        printf("Start/Goal not found.\n");
        return 1;
    }

    // BFS menghasilkan visited[][] dan path[][]
    int rows = g->rows;
    int cols = g->cols;

    int **visited = calloc(rows, sizeof(int*));
    int **final_path = calloc(rows, sizeof(int*));

    for (int i = 0; i < rows; i++) {
        visited[i] = calloc(cols, sizeof(int));
        final_path[i] = calloc(cols, sizeof(int));
    }

    bfs_visual(g, sr, sc, gr, gc, visited, final_path);


    // Tampilkan di SDL
    visualize_sdl(g, visited, final_path);

    grid_destroy(g);
    return 0;
}
