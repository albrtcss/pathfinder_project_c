#include <SDL2/SDL.h>
#include "../include/grid.h"
#include "../include/visualize_sdl.h"

#define CELL_SIZE 24
#define GRID_COLOR_EMPTY   0xFFFFFFFF  // putih
#define GRID_COLOR_OBS     0x000000FF  // hitam
#define GRID_COLOR_START   0x00FF00FF  // hijau
#define GRID_COLOR_GOAL    0xFF0000FF  // merah
#define GRID_COLOR_VISITED 0x00FFFFFF  // cyan
#define GRID_COLOR_PATH    0xFFFF00FF  // kuning

static void draw_cell(SDL_Renderer *r, int row, int col, SDL_Color color) {
    SDL_Rect rect = { col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE };
    SDL_SetRenderDrawColor(r, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(r, &rect);
}

/* Fungsi convert warna dari hex RGBA → SDL_Color */
static SDL_Color rgba(unsigned int hex) {
    SDL_Color c;
    c.r = (hex >> 24) & 0xFF;
    c.g = (hex >> 16) & 0xFF;
    c.b = (hex >> 8) & 0xFF;
    c.a = (hex) & 0xFF;
    return c;
}

void visualize_sdl(Grid *g, int **visited, int **path) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *win = SDL_CreateWindow(
        "Pathfinder SDL",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        g->cols * CELL_SIZE, g->rows * CELL_SIZE,
        0
    );

    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    int sr, sc, gr, gc;
    grid_find_start_goal(g, &sr, &sc, &gr, &gc);

    int running = 1;
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = 0;
        }

        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
        SDL_RenderClear(renderer);

        for (int r = 0; r < g->rows; r++) {
            for (int c = 0; c < g->cols; c++) {
                char cell = g->cells[r][c];
                SDL_Color color;

                if (r == sr && c == sc) color = rgba(GRID_COLOR_START);
                else if (r == gr && c == gc) color = rgba(GRID_COLOR_GOAL);
                else if (cell == '1') color = rgba(GRID_COLOR_OBS);
                else if (path && path[r][c]) color = rgba(GRID_COLOR_PATH);
                else if (visited && visited[r][c]) color = rgba(GRID_COLOR_VISITED);
                else color = rgba(GRID_COLOR_EMPTY);

                draw_cell(renderer, r, c, color);
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
