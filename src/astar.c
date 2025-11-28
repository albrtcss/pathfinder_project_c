#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include "../include/astar.h"
#include "../include/grid.h"

typedef struct {
    int r, c;
    int g; // cost from start
    int f; // g + h
} ANode;

static int heuristic(int r1, int c1, int r2, int c2) {
    // Manhattan
    return abs(r1 - r2) + abs(c1 - c2);
}

int astar(Grid* g, int sr, int sc, int gr, int gc,
          Coord* out_path, int* out_len, int* out_nodes_expanded)
{
    if (!g || !out_path || !out_len) return -2;
    int R = g->rows, C = g->cols;
    int maxnodes = R * C;
    int *closed = calloc(maxnodes, sizeof(int));
    int *open = calloc(maxnodes, sizeof(int)); // store index in heap? no, boolean for presence
    int *parent = malloc(sizeof(int) * maxnodes); // store parent index: pr*C+pc or -1
    int *gscore = malloc(sizeof(int) * maxnodes);
    for (int i=0;i<maxnodes;i++){ parent[i] = -1; gscore[i] = INT_MAX; }

    // min-heap of nodes (store index = r*C + c)
    int *heap = malloc(sizeof(int) * maxnodes);
    int heap_size = 0;

    // helper lambdas not available; implement functions locally
    ;

    // helper functions using static inline-like approach via inner functions not possible in C89.
    // We'll implement simple linear search insertion into heap based on f = g + h

    // initialize
    int start_idx = sr * C + sc;
    gscore[start_idx] = 0;
    heap[heap_size++] = start_idx;
    open[start_idx] = 1;
    parent[start_idx] = -1;
    int nodes_expanded = 0;

    while (heap_size > 0) {
        // find heap element with lowest f (linear search — ok for moderate sizes)
        int best_i = 0;
        int best_idx = heap[0];
        int best_f = gscore[best_idx] + heuristic(best_idx / C, best_idx % C, gr, gc);
        for (int i=1;i<heap_size;i++) {
            int idx = heap[i];
            int f = gscore[idx] + heuristic(idx / C, idx % C, gr, gc);
            if (f < best_f) { best_f = f; best_idx = idx; best_i = i; }
        }
        // pop best
        int cur_idx = best_idx;
        // remove heap[best_i]
        heap[best_i] = heap[heap_size-1];
        heap_size--;
        open[cur_idx] = 0;
        closed[cur_idx] = 1;

        int cr = cur_idx / C;
        int cc = cur_idx % C;

        nodes_expanded++;

        if (cr == gr && cc == gc) {
            // reconstruct path
            int plen = 0;
            int idx = cur_idx;
            while (idx != -1) {
                out_path[plen].r = idx / C;
                out_path[plen].c = idx % C;
                plen++;
                idx = parent[idx];
            }
            // reverse
            for (int i=0;i<plen/2;i++) {
                Coord tmp = out_path[i];
                out_path[i] = out_path[plen-i-1];
                out_path[plen-i-1] = tmp;
            }
            *out_len = plen;
            if (out_nodes_expanded) *out_nodes_expanded = nodes_expanded;
            free(closed); free(open); free(parent); free(gscore); free(heap);
            return 0;
        }

        // neighbors 4-way
        int dr[4] = {-1,1,0,0};
        int dc[4] = {0,0,-1,1};
        for (int k=0;k<4;k++) {
            int nr = cr + dr[k];
            int nc = cc + dc[k];
            if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
            if (g->cells[nr][nc] == '1') continue; // obstacle
            int nidx = nr * C + nc;
            if (closed[nidx]) continue;
            int tentative_g = gscore[cur_idx] + 1;
            if (tentative_g < gscore[nidx]) {
                parent[nidx] = cur_idx;
                gscore[nidx] = tentative_g;
                if (!open[nidx]) {
                    heap[heap_size++] = nidx;
                    open[nidx] = 1;
                }
            }
        }
    }

    // no path
    free(closed); free(open); free(parent); free(gscore); free(heap);
    if (out_nodes_expanded) *out_nodes_expanded = nodes_expanded;
    return -1;
}
