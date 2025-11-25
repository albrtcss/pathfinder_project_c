// src/visualize_ncurses.c
#include <ncurses.h>
#include "visualize_simple.h"

/* Animate path using ncurses (prefix path rendering) */
void animate_path_ncurses(Grid *g, const Coord *path, int path_len, int delay_ms) {
    if (!g || !path || path_len <= 0) return;

    initscr();
    noecho();
    curs_set(FALSE);

    for (int step = 0; step < path_len; ++step) {
        clear();

        /* draw grid */
        for (int r = 0; r < g->rows; ++r) {
            for (int c = 0; c < g->cols; ++c) {
                mvaddch(r, c, g->cells[r][c]);
            }
        }

        /* draw path prefix up to current step */
        for (int i = 1; i <= step && i < path_len - 1; ++i) {
            mvaddch(path[i].r, path[i].c, '*');
        }

        refresh();
        napms(delay_ms);
    }

    /* wait key to exit */
    getch();
    endwin();
}
