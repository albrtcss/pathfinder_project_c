#ifndef BFS_H
#define BFS_H

#include "grid.h"

int bfs_visual(
    Grid *g,
    int sr, int sc,
    int gr, int gc,
    int **visited,
    int **final_path
);

int bfs(Grid *g, int sr, int sc, int gr, int gc, Node *out_path, int *out_len);

#endif
