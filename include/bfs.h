#ifndef BFS_H
#define BFS_H

#include "grid.h"

typedef struct {
    int r;
    int c;
} Node;

int bfs(Grid* g, int sr, int sc, int gr, int gc, Node* out_path, int* out_len);

#endif
