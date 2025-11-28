#include <stdlib.h>
#include <string.h>
#include "../include/bfs.h"
#include "../include/grid.h"

int bfs(Grid* g, int sr, int sc, int gr, int gc, Node* out_path, int* out_len) {
    int R = g->rows, C = g->cols;
    int *visited = calloc(R * C, sizeof(int));
    int *pr = malloc(sizeof(int) * R * C);
    int *pc = malloc(sizeof(int) * R * C);
    for (int i=0;i<R*C;i++){ pr[i] = pc[i] = -1; }

    Node *queue = malloc(sizeof(Node) * R * C);
    int head = 0, tail = 0;
    queue[tail++] = (Node){sr, sc};
    visited[sr*C + sc] = 1;

    int dr[4] = {-1,1,0,0};
    int dc[4] = {0,0,-1,1};

    while (head < tail) {
        Node cur = queue[head++];
        if (cur.r == gr && cur.c == gc) break;
        for (int k=0;k<4;k++) {
            int nr = cur.r + dr[k];
            int nc = cur.c + dc[k];
            if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
            if (g->cells[nr][nc] == '1') continue;
            if (!visited[nr*C + nc]) {
                visited[nr*C + nc] = 1;
                pr[nr*C + nc] = cur.r;
                pc[nr*C + nc] = cur.c;
                queue[tail++] = (Node){nr, nc};
            }
        }
    }

    if (!visited[gr*C + gc]) {
        free(visited); free(pr); free(pc); free(queue);
        return -1;
    }

    int len = 0;
    int cr = gr, cc = gc;
    while (!(cr == sr && cc == sc)) {
        out_path[len++] = (Node){cr, cc};
        int idx = cr*C + cc;
        int tr = pr[idx], tc = pc[idx];
        cr = tr; cc = tc;
    }
    out_path[len++] = (Node){sr, sc};
    // reverse
    for (int i=0;i<len/2;i++) {
        Node tmp = out_path[i];
        out_path[i] = out_path[len-i-1];
        out_path[len-i-1] = tmp;
    }
    *out_len = len;
    free(visited); free(pr); free(pc); free(queue);
    return 0;
}

int bfs_visual(
    Grid *g,
    int sr, int sc,
    int gr, int gc,
    int **visited,
    int **final_path
) {
    int R = g->rows, C = g->cols;
    // init
    for (int r=0;r<R;r++) for (int c=0;c<C;c++) { visited[r][c] = 0; final_path[r][c] = 0; }

    Node *queue = malloc(sizeof(Node) * R * C);
    int *pr = malloc(sizeof(int) * R * C);
    int *pc = malloc(sizeof(int) * R * C);
    for (int i=0;i<R*C;i++) { pr[i]=pc[i]=-1; }

    int head=0, tail=0;
    queue[tail++] = (Node){sr, sc};
    visited[sr][sc] = 1;

    int dr[4] = {-1,1,0,0};
    int dc[4] = {0,0,-1,1};

    while (head < tail) {
        Node cur = queue[head++];
        if (cur.r == gr && cur.c == gc) break;
        for (int k=0;k<4;k++) {
            int nr = cur.r + dr[k];
            int nc = cur.c + dc[k];
            if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
            if (g->cells[nr][nc] == '1') continue;
            if (!visited[nr][nc]) {
                visited[nr][nc] = 1;
                pr[nr*C + nc] = cur.r;
                pc[nr*C + nc] = cur.c;
                queue[tail++] = (Node){nr, nc};
            }
        }
    }

    if (!visited[gr][gc]) {
        free(queue); free(pr); free(pc);
        return -1;
    }

    // reconstruct final_path
    int cr = gr, cc = gc;
    while (!(cr == sr && cc == sc)) {
        final_path[cr][cc] = 1;
        int idx = cr*C + cc;
        int tr = pr[idx], tc = pc[idx];
        cr = tr; cc = tc;
    }
    final_path[sr][sc] = 1;

    free(queue); free(pr); free(pc);
    return 0;
}
