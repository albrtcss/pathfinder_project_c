// src/visualize_simple.c
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "visualize_simple.h"

#ifdef _WIN32
  #include <windows.h>
  static void sleep_ms(int ms) { Sleep(ms); }
  static void clear_screen(void) { system("cls"); }
#else
  #include <unistd.h>
  static void sleep_ms(int ms) { usleep(ms * 1000); }
  static void clear_screen(void) { printf("\033[H\033[J"); }
#endif

/* Copy grid cells (deep copy) */
static char **dup_cells(const Grid *g) {
    if (!g) return NULL;
    char **copy = malloc(sizeof(char*) * g->rows);
    if (!copy) return NULL;
    for (int r = 0; r < g->rows; ++r) {
        copy[r] = strdup(g->cells[r]);
        if (!copy[r]) {
            for (int i = 0; i < r; ++i) free(copy[i]);
            free(copy);
            return NULL;
        }
    }
    return copy;
}

static void free_cells_copy(char **copy, int rows) {
    if (!copy) return;
    for (int r = 0; r < rows; ++r) free(copy[r]);
    free(copy);
}

/* Print array of strings */
static void print_cells(char **cells, int rows) {
    for (int r = 0; r < rows; ++r) {
        puts(cells[r]);
    }
}

/* Animate path step-by-step. Path is array Coord (start..goal) */
void animate_path(Grid *g, const Coord *path, int path_len, int delay_ms) {
    if (!g || !path || path_len <= 0) return;

    char **copy = dup_cells(g);
    if (!copy) return;

    for (int i = 0; i < path_len; ++i) {
        int r = path[i].r;
        int c = path[i].c;

        /* Jangan timpa S atau G; hanya beri tanda untuk intermediate */
        if (i != 0 && i != path_len - 1) {
            /* pastikan indeks dalam range */
            if (r >= 0 && r < g->rows && c >= 0 && c < g->cols) {
                copy[r][c] = '*';
            }
        }

        clear_screen();
        print_cells(copy, g->rows);
        fflush(stdout);
        sleep_ms(delay_ms);
    }

    /* beri jeda kecil saat selesai */
    sleep_ms(200);
    free_cells_copy(copy, g->rows);
}
