#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/grid.h"

#define MAX_LINE 4096

static char *str_dup(const char *s) {
    if (!s) return NULL;
    char *d = malloc(strlen(s) + 1);
    if (d) strcpy(d, s);
    return d;
}

static char *read_line_strip_newline(FILE *f) {
    char buf[MAX_LINE];
    if (!fgets(buf, sizeof(buf), f)) return NULL;
    size_t len = strlen(buf);
    while (len && (buf[len-1] == '\n' || buf[len-1] == '\r')) {
        buf[--len] = '\0';
    }
    return str_dup(buf);
}

Grid *grid_create_from_file(const char *path) {
    if (!path) return NULL;
    FILE *f = fopen(path, "r");
    if (!f) return NULL;

    char **lines = NULL;
    size_t count = 0;
    char *ln;
    while ((ln = read_line_strip_newline(f)) != NULL) {
        if (strlen(ln) == 0) { free(ln); continue; }
        char **tmp = realloc(lines, (count + 1) * sizeof(char*));
        if (!tmp) { free(ln); for (size_t i=0;i<count;i++) free(lines[i]); free(lines); fclose(f); return NULL; }
        lines = tmp;
        lines[count++] = ln;
    }
    fclose(f);
    if (count == 0) return NULL;

    int cols = (int)strlen(lines[0]);
    for (size_t i = 1; i < count; ++i) {
        if ((int)strlen(lines[i]) != cols) {
            for (size_t j=0;j<count;j++) free(lines[j]);
            free(lines);
            return NULL;
        }
    }

    Grid *g = malloc(sizeof(Grid));
    if (!g) { for (size_t j=0;j<count;j++) free(lines[j]); free(lines); return NULL; }

    g->rows = (int)count;
    g->cols = cols;
    g->cells = malloc(sizeof(char*) * g->rows);
    if (!g->cells) { free(g); for (size_t j=0;j<count;j++) free(lines[j]); free(lines); return NULL; }

    for (int r = 0; r < g->rows; ++r) {
        g->cells[r] = lines[r]; // take ownership of string
    }
    free(lines);
    return g;
}

void grid_destroy(Grid *g) {
    if (!g) return;
    for (int r=0;r<g->rows;r++) free(g->cells[r]);
    free(g->cells);
    free(g);
}

void grid_print(Grid *g) {
    if (!g) return;
    for (int r=0;r<g->rows;r++) {
        printf("%s\n", g->cells[r]);
    }
}

char grid_get(Grid *g, int r, int c) {
    if (!g) return '\0';
    if (r < 0 || r >= g->rows || c < 0 || c >= g->cols) return '\0';
    return g->cells[r][c];
}

void grid_set_obstacle(Grid *g, int r, int c) {
    if (!g) return;
    if (r < 0 || r >= g->rows || c < 0 || c >= g->cols) return;
    g->cells[r][c] = '1';
}

int grid_find_start_goal(Grid *g, int *sr, int *sc, int *gr, int *gc) {
    if (!g || !sr || !sc || !gr || !gc) return -1;
    *sr = *sc = *gr = *gc = -1;
    for (int r=0;r<g->rows;r++) {
        for (int c=0;c<g->cols;c++) {
            char ch = g->cells[r][c];
            if (ch == 'S') { *sr = r; *sc = c; }
            if (ch == 'G') { *gr = r; *gc = c; }
        }
    }
    return (*sr != -1 && *gr != -1) ? 0 : -1;
}

Grid* grid_clone(const Grid *src) {
    if (!src) return NULL;
    Grid *g = malloc(sizeof(Grid));
    g->rows = src->rows;
    g->cols = src->cols;
    g->cells = malloc(sizeof(char*) * g->rows);
    for (int r=0;r<g->rows;r++) {
        g->cells[r] = malloc(g->cols + 1);
        memcpy(g->cells[r], src->cells[r], g->cols);
        g->cells[r][g->cols] = '\0';
    }
    return g;
}
