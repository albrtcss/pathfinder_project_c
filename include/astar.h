#ifndef ASTAR_H
#define ASTAR_H

#include "grid.h"

/* Coord used for path output */
typedef struct {
    int r, c;
} Coord;

/*
 * astar:
 *   g: pointer to Grid
 *   sr,sc: start row/col
 *   gr,gc: goal row/col
 *   out_path: array of Coord to receive path (caller-allocated)
 *   out_len: pointer to receive path length
 *   out_nodes_expanded: optional pointer to receive nodes expanded (can be NULL)
 *
 * Returns 0 on success (path found), -1 if no path found, -2 on other error.
 */
int astar(Grid* g, int sr, int sc, int gr, int gc,
          Coord* out_path, int* out_len, int* out_nodes_expanded);

#endif // ASTAR_H
