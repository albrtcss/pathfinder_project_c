#include <stdio.h>
#include "grid.h"
#include "bfs.h"

int main() {
    Grid* g = grid_create_from_file("maps/map1.txt");
    if (!g) {
        printf("Gagal memuat map.\n");
        return 1;
    }

    printf("Map loaded\n");
    grid_print(g);

    int sr, sc, gr, gc;
    if (grid_find_start_goal(g, &sr, &sc, &gr, &gc) != 0) {
        printf("Start/Goal tidak ditemukan.\n");
        grid_destroy(g);
        return 1;
    }

    printf("Start: (%d,%d)\n", sr, sc);
    printf("Goal:  (%d,%d)\n", gr, gc);

    Node path[10000];
    int path_len = 0;

    int found = bfs(g, sr, sc, gr, gc, path, &path_len);

    if (found)
        printf("Path ditemukan! Panjang = %d\n", path_len);
    else
        printf("Tidak ada path.\n");

    grid_destroy(g);
    return 0;
}
