// src/grid.c
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/grid.h"

/* Cross-platform safe line reader using fgets.
   We'll allocate a buffer per line (max length 1024). If you expect longer lines,
   increase MAX_LINE. */
#define MAX_LINE 1024

static char* str_dup(const char *s) {
    char *d = malloc(strlen(s) + 1);
    if (d) strcpy(d, s);
    return d;
}

/* Read a line and strip newline. Returns malloc'ed string, or NULL on EOF. */
static char *read_line_strip_newline(FILE *f) {
    char buf[MAX_LINE];
    if (fgets(buf, sizeof(buf), f) == NULL) return NULL;
    size_t len = strlen(buf);
    if (len > 0 && buf[len-1] == '\n') buf[len-1] = '\0';
    return str_dup(buf);
}

Grid *grid_create_from_file(const char *path) {
    FILE *f = fopen(path, "r");
    if (!f) return NULL;

    char **lines = NULL;
    size_t count = 0;
    char *ln;
    while ((ln = read_line_strip_newline(f)) != NULL) {
        if (strlen(ln) == 0) { free(ln); continue; } // skip blank
        char *trimmed = ln; // already trimmed newline
        // allocate lines array
        char **tmp = realloc(lines, (count + 1) * sizeof(char*));
        if (!tmp) { free(ln); for (size_t i=0;i<count;i++) free(lines[i]); free(lines); fclose(f); return NULL; }
        lines = tmp;
        lines[count++] = trimmed;
    }
    fclose(f);

    if (count == 0) { free(lines); return NULL; }

    int cols = (int)strlen(lines[0]);
    for (size_t i = 1; i < count; ++i) {
        if ((int)strlen(lines[i]) != cols) {
            // cleanup
            for (size_t j = 0; j < count; ++j) free(lines[j]);
            free(lines);
            return NULL; // inconsistent row length
        }
    }

    Grid *g = malloc(sizeof(Grid));
    if (!g) { for (size_t j=0;j<count;j++) free(lines[j]); free(lines); return NULL; }

    g->rows = (int)count;
    g->cols = cols;
    g->cells = malloc(g->rows * sizeof(char*));
    if (!g->cells) { free(g); for (size_t j=0;j<count;j++) free(lines[j]); free(lines); return NULL; }

    for (int r = 0; r < g->rows; ++r) g->cells[r] = lines[r]; // transfer ownership
    free(lines); // only the array pointer (strings kept)

    return g;
}

void grid_destroy(Grid *g) {
    if (!g) return;
    for (int i = 0; i < g->rows; ++i) free(g->cells[i]);
    free(g->cells);
    free(g);
}

void grid_print(Grid *g) {
    if (!g) return;
    for (int r = 0; r < g->rows; ++r) {
        printf("%s\n", g->cells[r]);
    }
}

int grid_find_start_goal(Grid *g, int *sr, int *sc, int *gr, int *gc) {
    if (!g) return -1;
    *sr = *sc = *gr = *gc = -1;
    for (int r = 0; r < g->rows; ++r) {
        for (int c = 0; c < g->cols; ++c) {
            char ch = g->cells[r][c];
            if (ch == 'S') { *sr = r; *sc = c; }
            else if (ch == 'G') { *gr = r; *gc = c; }
        }
    }
    return (*sr != -1 && *gr != -1) ? 0 : -1;
}
