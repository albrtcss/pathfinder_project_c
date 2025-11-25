// include/visualize_simple.h
#ifndef VISUALIZE_SIMPLE_H
#define VISUALIZE_SIMPLE_H

#include "grid.h"
#include "astar.h"   /* untuk typedef Coord; jika pakai BFS, adaptasikan */

void animate_path(Grid *g, const Coord *path, int path_len, int delay_ms);

#endif // VISUALIZE_SIMPLE_H
