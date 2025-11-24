#ifndef BFS_H
#define BFS_H

#include "grid.h"

typedef struct {
    int r, c;
} Node;

/* 
   BFS:
   Mengembalikan 1 jika path ditemukan, 0 jika tidak.
   out_path = array Node untuk menyimpan jalur
   out_len  = panjang path
*/
int bfs(Grid* g, int sr, int sc, int gr, int gc, Node* out_path, int* out_len);

#endif
