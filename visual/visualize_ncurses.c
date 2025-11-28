#include <pdcurses.h>
#include <unistd.h>
#include <string.h>
#include "../include/visualize_ncurses.h"

void visualize_ncurses(Grid *g, Node *path, int path_len, int delay_ms) {
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_WHITE, COLOR_BLACK); // empty
        init_pair(2, COLOR_BLACK, COLOR_WHITE); // obstacle
        init_pair(3, COLOR_GREEN, COLOR_BLACK); // start
        init_pair(4, COLOR_RED, COLOR_BLACK);   // goal
        init_pair(5, COLOR_YELLOW, COLOR_BLACK);// path
    }

    // draw base map
    for (int r=0;r<g->rows;r++) {
        for (int c=0;c<g->cols;c++) {
            char ch = g->cells[r][c];
            if (has_colors()) {
                if (ch == '1') attron(COLOR_PAIR(2));
                else mvaddch(r, c, (ch=='0')?'.':ch);
                if (ch == '1') attroff(COLOR_PAIR(2));
            } else {
                mvaddch(r, c, (ch=='0')?'.':ch);
            }
        }
    }
    refresh();

    int paused = 0;
    int step = 0;
    int ch;
    while (step < path_len) {
        // handle input non-blocking
        nodelay(stdscr, TRUE);
        ch = getch();
        if (ch == 'q' || ch == 'Q' || ch == 27) { // ESC or q
            break;
        } else if (ch == ' ') {
            paused = !paused;
        } else if (ch == 'r' || ch == 'R') {
            // replay
            for (int i=0;i<g->rows;i++) {
                for (int j=0;j<g->cols;j++) {
                    char chcell = g->cells[i][j];
                    mvaddch(i,j,(chcell=='0')?'.':chcell);
                }
            }
            step = 0;
            paused = 0;
        } else if (ch == '+') {
            if (delay_ms > 10) delay_ms -= 10;
        } else if (ch == '-') {
            delay_ms += 10;
        }
        nodelay(stdscr, FALSE);

        if (!paused) {
            int r = path[step].r;
            int c = path[step].c;
            if (g->cells[r][c] != 'S' && g->cells[r][c] != 'G') {
                if (has_colors()) {
                    attron(COLOR_PAIR(5));
                    mvaddch(r, c, '*');
                    attroff(COLOR_PAIR(5));
                } else {
                    mvaddch(r, c, '*');
                }
            }
            step++;
            mvprintw(g->rows + 1, 0, "SPACE:pause  +/-:change delay (ms)  r:replay  q:quit   delay=%dms", delay_ms);
            refresh();
            usleep(delay_ms * 1000);
        } else {
            // paused, small sleep to avoid busy loop
            usleep(100000);
        }
    }

    mvprintw(g->rows + 2, 0, "Press any key to exit...");
    nodelay(stdscr, FALSE);
    getch();
    endwin();
}
