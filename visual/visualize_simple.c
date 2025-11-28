#include <stdio.h>
#include <unistd.h>
#include "../include/grid.h"
#include "../include/astar.h"

void visualize_simple(Grid *g, Node *path, int path_len) {
    Grid *clone = grid_clone(g);
    for (int i=0;i<path_len;i++) {
        int r = path[i].r;
        int c = path[i].c;
        if (clone->cells[r][c] != 'S' && clone->cells[r][c] != 'G')
            clone->cells[r][c] = '*';
        // clear screen
        printf("\033[H\033[J");
        for (int rr=0; rr<clone->rows; rr++) {
            printf("%s\n", clone->cells[rr]);
        }
        usleep(120000);
    }
    grid_destroy(clone);
}
