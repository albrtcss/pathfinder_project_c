#ifndef BFS_H
#define BFS_H

#include "grid.h"

int bfs(Grid *g, int sr, int sc, int gr, int gc, Node *out_path, int *out_len);

/* bfs_visual: fills visited[][] and final_path[][] (caller-allocates int** arrays)
   visited[r][c] becomes 1 if visited; final_path[r][c] becomes 1 if part of final path.
*/
int bfs_visual(
    Grid *g,
    int sr, int sc,
    int gr, int gc,
    int **visited,
    int **final_path
);

#endif // BFS_H
