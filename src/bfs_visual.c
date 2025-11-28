#include <stdlib.h>
#include "../include/bfs.h"
#include "../include/grid.h"

typedef struct {
    int r, c;
} QNode;

int bfs_visual(Grid *g, int sr, int sc, int gr, int gc,
               int **visited, int **final_path)
{
    int R = g->rows, C = g->cols;

    QNode *queue = malloc(R * C * sizeof(QNode));
    int **parent_r = malloc(R * sizeof(int*));
    int **parent_c = malloc(R * sizeof(int*));

    for (int i = 0; i < R; i++) {
        parent_r[i] = malloc(C * sizeof(int));
        parent_c[i] = malloc(C * sizeof(int));
        for (int j = 0; j < C; j++) {
            parent_r[i][j] = -1;
            parent_c[i][j] = -1;
        }
    }

    int head = 0, tail = 0;

    queue[tail++] = (QNode){sr, sc};
    visited[sr][sc] = 1;

    int dr[4] = {1, -1, 0, 0};
    int dc[4] = {0, 0, 1, -1};

    while (head < tail) {
        QNode cur = queue[head++];

        if (cur.r == gr && cur.c == gc)
            break;

        for (int k = 0; k < 4; k++) {
            int nr = cur.r + dr[k];
            int nc = cur.c + dc[k];

            if (nr < 0 || nr >= R || nc < 0 || nc >= C)
                continue;

            if (visited[nr][nc]) continue;
            if (g->cells[nr][nc] == '1') continue;

            visited[nr][nc] = 1;
            parent_r[nr][nc] = cur.r;
            parent_c[nr][nc] = cur.c;

            queue[tail++] = (QNode){nr, nc};
        }
    }

    // Rekonstruksi jalur
    int r = gr, c = gc;
    while (!(r == sr && c == sc)) {
        final_path[r][c] = 1;
        int pr = parent_r[r][c];
        int pc = parent_c[r][c];
        if (pr == -1 && pc == -1) break; // tidak ada jalur
        r = pr;
        c = pc;
    }
    final_path[sr][sc] = 1;

    // free memory
    for (int i = 0; i < R; i++) {
        free(parent_r[i]);
        free(parent_c[i]);
    }
    free(parent_r);
    free(parent_c);
    free(queue);

    return 1;
}
