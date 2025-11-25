#include "../include/grid.h"
#include "../include/bfs.h"


typedef struct {
    int r;
    int c;
} Parent;

int bfs(Grid* g, int sr, int sc, int gr, int gc, Node* out_path, int* out_len) {
    int R = g->rows;
    int C = g->cols;

    int visited[R][C];
    Parent parent[R][C];

    for (int r = 0; r < R; r++)
        for (int c = 0; c < C; c++) {
            visited[r][c] = 0;
            parent[r][c].r = -1;
            parent[r][c].c = -1;
        }

    Node queue[10000];
    int head = 0, tail = 0;

    queue[tail++] = (Node){sr, sc};
    visited[sr][sc] = 1;

    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    while (head < tail) {
        Node cur = queue[head++];
        if (cur.r == gr && cur.c == gc) break;

        for (int i = 0; i < 4; i++) {
            int nr = cur.r + dr[i];
            int nc = cur.c + dc[i];

            if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
            if (g->cells[nr][nc] == '1') continue;
            if (!visited[nr][nc]) {
                visited[nr][nc] = 1;
                parent[nr][nc].r = cur.r;
                parent[nr][nc].c = cur.c;
                queue[tail++] = (Node){nr, nc};
            }
        }
    }

    if (!visited[gr][gc]) return -1;

    int len = 0;
    int cr = gr, cc = gc;

    while (!(cr == sr && cc == sc)) {
        out_path[len++] = (Node){cr, cc};
        Parent p = parent[cr][cc];
        cr = p.r;
        cc = p.c;
    }

    out_path[len++] = (Node){sr, sc};

    for (int i = 0; i < len / 2; i++) {
        Node tmp = out_path[i];
        out_path[i] = out_path[len - i - 1];
        out_path[len - i - 1] = tmp;
    }

    *out_len = len;
    return 0;
}
