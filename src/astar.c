#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "astar.h"

/* helpers */
static inline int idx(Grid* g, int r, int c) { return r * g->cols + c; }
static inline int manhattan(int r1,int c1,int r2,int c2){ return abs(r1-r2)+abs(c1-c2); }

/* Dynamic min-heap storing integer node ids (flattened index).
   We compare using an external fscore array passed into push/pop. */
typedef struct {
    int *data;
    int size;
    int cap;
} MinHeap;

static MinHeap* heap_create(int cap) {
    MinHeap* h = malloc(sizeof(MinHeap));
    if (!h) return NULL;
    h->data = malloc(sizeof(int) * cap);
    if (!h->data) { free(h); return NULL; }
    h->size = 0;
    h->cap = cap;
    return h;
}

static void heap_free(MinHeap* h) {
    if (!h) return;
    free(h->data);
    free(h);
}

static int heap_resize(MinHeap* h) {
    int newcap = h->cap * 2;
    int *tmp = realloc(h->data, sizeof(int) * newcap);
    if (!tmp) return -1;
    h->data = tmp;
    h->cap = newcap;
    return 0;
}

static void heap_swap(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}

/* sift-up using fscore pointer */
static void heap_sift_up(MinHeap* h, int i, const int *fscore) {
    while (i > 0) {
        int p = (i - 1) / 2;
        if (fscore[h->data[i]] < fscore[h->data[p]]) {
            heap_swap(&h->data[i], &h->data[p]);
            i = p;
        } else break;
    }
}

/* sift-down using fscore pointer */
static void heap_sift_down(MinHeap* h, int i, const int *fscore) {
    for (;;) {
        int l = 2*i + 1;
        int r = l + 1;
        int smallest = i;
        if (l < h->size && fscore[h->data[l]] < fscore[h->data[smallest]]) smallest = l;
        if (r < h->size && fscore[h->data[r]] < fscore[h->data[smallest]]) smallest = r;
        if (smallest != i) {
            heap_swap(&h->data[i], &h->data[smallest]);
            i = smallest;
        } else break;
    }
}

/* push id into heap (duplicates allowed) */
static int heap_push(MinHeap* h, int id, const int *fscore) {
    if (h->size >= h->cap) {
        if (heap_resize(h) != 0) return -1;
    }
    h->data[h->size] = id;
    heap_sift_up(h, h->size, fscore);
    h->size++;
    return 0;
}

/* pop minimum id; returns -1 if empty; out_fscore optionally filled */
static int heap_pop(MinHeap* h, const int *fscore) {
    if (h->size == 0) return -1;
    int out = h->data[0];
    h->size--;
    if (h->size > 0) {
        h->data[0] = h->data[h->size];
        heap_sift_down(h, 0, fscore);
    }
    return out;
}

/* Main A* implementation */
int astar(Grid* g, int sr, int sc, int gr, int gc,
          Coord* out_path, int* out_len, int* out_nodes_expanded) {
    if (!g || !out_path || !out_len) return -2;
    if (sr < 0 || sc < 0 || gr < 0 || gc < 0) return -2;
    int R = g->rows;
    int C = g->cols;
    int N = R * C;

    int *gscore = malloc(N * sizeof(int));
    int *fscore = malloc(N * sizeof(int));
    int *came_from = malloc(N * sizeof(int));
    char *in_closed = calloc(N, 1);
    char *in_open = calloc(N, 1);

    if (!gscore || !fscore || !came_from || !in_closed || !in_open) {
        free(gscore); free(fscore); free(came_from); free(in_closed); free(in_open);
        return -2;
    }

    for (int i = 0; i < N; ++i) {
        gscore[i] = INT_MAX;
        fscore[i] = INT_MAX;
        came_from[i] = -1;
    }

    int start = idx(g, sr, sc);
    int goal = idx(g, gr, gc);

    gscore[start] = 0;
    fscore[start] = manhattan(sr, sc, gr, gc);

    MinHeap* open = heap_create(1024);
    if (!open) {
        free(gscore); free(fscore); free(came_from); free(in_closed); free(in_open);
        return -2;
    }
    if (heap_push(open, start, fscore) != 0) {
        heap_free(open);
        free(gscore); free(fscore); free(came_from); free(in_closed); free(in_open);
        return -2;
    }
    in_open[start] = 1;

    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};
    int nodes_expanded = 0;
    int found = 0;

    while (open->size > 0) {
        int current = heap_pop(open, fscore);
        if (current < 0) break;
        /* If node already closed (we may have duplicates), skip */
        if (in_closed[current]) continue;

        in_open[current] = 0;
        in_closed[current] = 1;
        nodes_expanded++;

        if (current == goal) {
            found = 1;
            break;
        }

        int cr = current / C;
        int cc = current % C;

        for (int k = 0; k < 4; ++k) {
            int nr = cr + dr[k];
            int nc = cc + dc[k];
            if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
            char ch = g->cells[nr][nc];
            if (ch == '1' || ch == '#') continue;
            int neighbor = idx(g, nr, nc);
            if (in_closed[neighbor]) continue;
            int tentative_g = (gscore[current] == INT_MAX) ? INT_MAX : gscore[current] + 1;
            if (tentative_g < gscore[neighbor]) {
                came_from[neighbor] = current;
                gscore[neighbor] = tentative_g;
                fscore[neighbor] = tentative_g + manhattan(nr, nc, gr, gc);
                if (!in_open[neighbor]) {
                    if (heap_push(open, neighbor, fscore) != 0) {
                        /* memory error -> clean up and exit */
                        heap_free(open);
                        free(gscore); free(fscore); free(came_from); free(in_closed); free(in_open);
                        return -2;
                    }
                    in_open[neighbor] = 1;
                }
            }
        }
    }

    if (!found) {
        heap_free(open);
        free(gscore); free(fscore); free(came_from); free(in_closed); free(in_open);
        if (out_nodes_expanded) *out_nodes_expanded = nodes_expanded;
        *out_len = 0;
        return -1;
    }

    /* reconstruct path from goal -> start */
    int cur = goal;
    int plen = 0;
    while (cur != -1) {
        int r = cur / C;
        int c = cur % C;
        out_path[plen].r = r;
        out_path[plen].c = c;
        plen++;
        if (cur == start) break;
        cur = came_from[cur];
    }

    /* reverse to start->goal */
    for (int i = 0; i < plen / 2; ++i) {
        Coord tmp = out_path[i];
        out_path[i] = out_path[plen - i - 1];
        out_path[plen - i - 1] = tmp;
    }

    if (out_nodes_expanded) *out_nodes_expanded = nodes_expanded;
    *out_len = plen;

    heap_free(open);
    free(gscore); free(fscore); free(came_from); free(in_closed); free(in_open);
    return 0;
}
