// include/grid.h
#ifndef GRID_H
#define GRID_H

typedef struct {
    int rows;
    int cols;
    char **cells;
} Grid;

Grid *grid_create_from_file(const char *path);
void grid_destroy(Grid *g);
void grid_print(Grid *g);
int grid_find_start_goal(Grid *g, int *sr, int *sc, int *gr, int *gc);
void grid_set_obstacle(Grid *g, int r, int c);

#endif
