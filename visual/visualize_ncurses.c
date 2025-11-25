// visual/visualize_ncurses.c
#include <ncursesw/ncurses.h>   // pakai versi wide-char untuk Windows
#include <unistd.h>
#include "../include/visualize_ncurses.h"
#include "../include/grid.h"

void visualize_ncurses(Grid *g, Node *path, int path_len) {
    if (!g || !path || path_len <= 0) return;

    initscr();
    noecho();
    curs_set(FALSE);

    for (int step = 0; step < path_len; step++) {
        clear();

        /* =====================
           PRINT GRID
        ====================== */
        for (int r = 0; r < g->rows; r++) {
            for (int c = 0; c < g->cols; c++) {
                char cell = g->cells[r][c];

                if (cell == '1') mvprintw(r, c, "#");       // obstacle
                else if (cell == 'S') mvprintw(r, c, "S");  // start
                else if (cell == 'G') mvprintw(r, c, "G");  // goal
                else mvprintw(r, c, ".");                  // empty
            }
        }

        /* =====================
           DRAW PATH UP TO STEP
        ====================== */
        for (int i = 0; i <= step; i++) {
            int rr = path[i].r;
            int cc = path[i].c;

            if (g->cells[rr][cc] != 'S' && g->cells[rr][cc] != 'G')
                mvprintw(rr, cc, "*");
        }

        refresh();
        usleep(120000);  // 120ms delay
    }

    mvprintw(g->rows + 1, 0, "Press any key to exit...");
    getch();
    endwin();
}
