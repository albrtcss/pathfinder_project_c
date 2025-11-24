#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/grid.h"

#define MAX_LINE 1024

// Duplicate string safely
static char* str_dup(const char *s) {
    char *d = malloc(strlen(s) + 1);
    if (d) strcpy(d, s);
    return d;
}

// Read one line, strip newline, return malloc'ed buffer
static char *read_line_strip_newline(FILE *f) {
    char buf[MAX_LINE];
    if (!fgets(buf, sizeof(buf), f)) return NULL;

    size_t len = strlen(buf);
    if (len && buf[len - 1] == '\n')
        buf[len - 1] = '\0';

    return str_dup(buf);
}

// Create grid from text file
Grid *grid_create_from_file(const char *path) {
    FILE *f = fopen(path, "r");
    if (!f) return NULL;

    char **lines = NULL;
    size_t count = 0;

    char *ln;
    while ((ln = read_line_strip_newline(f)) != NULL) {
        if (strlen(ln) == 0) {
            free(ln);
            continue;
        }

        char **tmp = realloc(lines, (count + 1) * sizeof(char*));
        if (!tmp) {
            free(ln);
            for (size_t i = 0; i < count; i++) free(lines[i]);
            free(lines);
            fclose(f);
            return NULL;
        }

        lines = tmp;
        lines[count++] = ln;
    }

    fclose(f);
    if (count == 0) return NULL;

    int cols = strlen(lines[0]);
    for (size_t i = 1; i < count; i++) {
        if ((int)strlen(lines[i]) != cols) {
            for (size_t j = 0; j < count; j++) free(lines[j]);
            free(lines);
            return NULL;
        }
    }

    Grid *g = malloc(sizeof(Grid));
    if (!g) {
        for (size_t j = 0; j < count; j++) free(lines[j]);
        free(lines);
        return NULL;
    }

    g->rows = count;
    g->cols = cols;
    g->cells = malloc(count * sizeof(char*));

    for (int r = 0; r < g->rows; r++)
        g->cells[r] = lines[r];

    free(lines);
    return g;
}

void grid_destroy(Grid *g) {
    if (!g) return;
    for (int i = 0; i < g->rows; i++)
        free(g->cells[i]);
    free(g->cells);
    free(g);
}

void grid_print(Grid *g) {
    if (!g) return;
    for (int r = 0; r < g->rows; r++)
        printf("%s\n", g->cells[r]);
}

int grid_find_start_goal(Grid *g, int *sr, int *sc, int *gr, int *gc) {
    *sr = *sc = *gr = *gc = -1;

    for (int r = 0; r < g->rows; r++) {
        for (int c = 0; c < g->cols; c++) {
            char ch = g->cells[r][c];
            if (ch == 'S') {
                *sr = r;
                *sc = c;
            }
            if (ch == 'G') {
                *gr = r;
                *gc = c;
            }
        }
    }

    return (*sr != -1 && *gr != -1) ? 0 : -1;
}

void grid_set_obstacle(Grid *g, int r, int c) {
    if (r >= 0 && r < g->rows && c >= 0 && c < g->cols)
        g->cells[r][c] = '1';
}
