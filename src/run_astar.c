#include <stdio.h>
#include <time.h>
#include "grid.h"
#include "astar.h"

/* Sample: if you want to show the screenshot reference used during development:
   /mnt/data/ecc0bbe8-1eab-46c1-9f5b-7f895d3effbb.png
   (This is a local path to your uploaded file.)
*/

int main(void) {
    Grid* g = grid_create_from_file("maps/map1.txt");
    if (!g) {
        fprintf(stderr, "Failed to load map\n");
        return 1;
    }

    printf("Map loaded:\n");
    grid_print(g);

    int sr, sc, gr, gc;
    if (grid_find_start_goal(g, &sr, &sc, &gr, &gc) != 0) {
        fprintf(stderr, "Start/Goal not found in map\n");
        grid_destroy(g);
        return 1;
    }

    printf("Start: (%d,%d)\n", sr, sc);
    printf("Goal:  (%d,%d)\n\n", gr, gc);

    Coord path[10000];
    int path_len = 0;
    int nodes_expanded = 0;
    clock_t t0 = clock();
    int res = astar(g, sr, sc, gr, gc, path, &path_len, &nodes_expanded);
    double elapsed = (double)(clock() - t0) / CLOCKS_PER_SEC;

    if (res == 0) {
        printf("A* Path found! Steps: %d, nodes_expanded: %d, time: %.6f s\n",
               path_len - 1, nodes_expanded, elapsed);
        for (int i = 1; i < path_len - 1; ++i) {
            g->cells[path[i].r][path[i].c] = '*';
        }
        grid_print(g);
    } else if (res == -1) {
        printf("A* did not find a path. nodes_expanded=%d\n", nodes_expanded);
    } else {
        printf("A* error (memory or input)\n");
    }

    grid_destroy(g);
    return 0;
}
