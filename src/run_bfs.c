#include <stdio.h>
#include "grid.h"
#include "bfs.h"

int main() {
    Grid* g = grid_create_from_file("maps/map1.txt");

    printf("Map loaded:\n");
    grid_print(g);

    int sr, sc, gr, gc;
    grid_find_start_goal(g, &sr, &sc, &gr, &gc);

    printf("Start: (%d,%d)\n", sr, sc);
    printf("Goal:  (%d,%d)\n\n", gr, gc);

    Node path[10000];
    int path_len = 0;

    if (bfs(g, sr, sc, gr, gc, path, &path_len) == 0) {
        printf("Path found! Steps: %d\n", path_len - 1);

        for (int i = 1; i < path_len - 1; i++) {
            g->cells[path[i].r][path[i].c] = '*';
        }
        grid_print(g);
    } else {
        printf("No path found.\n");
    }

    grid_destroy(g);
    return 0;
}
