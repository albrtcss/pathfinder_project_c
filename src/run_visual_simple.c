#include <stdio.h>
#include <stdlib.h>
#include "../include/grid.h"
#include "../include/astar.h"
#include "../include/astar.h"

extern void visualize_simple(Grid *g, Node *path, int path_len);

int main() {
    Grid *g = grid_create_from_file("maps/map1.txt");
    if (!g) {
        fprintf(stderr, "Failed to load map\n");
        return 1;
    }

    int sr, sc, gr, gc;
    if (grid_find_start_goal(g, &sr, &sc, &gr, &gc) != 0) {
        fprintf(stderr, "Start/Goal not found\n");
        grid_destroy(g);
        return 1;
    }

    Coord path[4096];
    int path_len = 0;
    int nodes_exp = 0;

    int ok = astar(g, sr, sc, gr, gc, path, &path_len, &nodes_exp);
    if (ok != 0) {
        printf("No path found (astar returned %d)\n", ok);
        grid_destroy(g);
        return 0;
    }

    // convert to Node for visualize_simple
    Node node_path[4096];
    for (int i=0;i<path_len;i++) { node_path[i].r = path[i].r; node_path[i].c = path[i].c; }

    printf("Map loaded:\n");
    grid_print(g);
    printf("Start: (%d,%d)\nGoal: (%d,%d)\n\n", sr, sc, gr, gc);
    printf("A* Path found! Steps: %d, nodes_expanded: %d\n", path_len, nodes_exp);

    visualize_simple(g, node_path, path_len);

    grid_destroy(g);
    return 0;
}
