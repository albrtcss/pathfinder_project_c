#ifndef GRID_H
#define GRID_H

typedef struct {
    int r, c;
} Node;

typedef struct {
    int rows;
    int cols;
    char **cells;
} Grid;

/* Membaca grid dari file teks (format baris sama panjang).
   Mengembalikan pointer Grid (malloc'ed) atau NULL jika gagal. */
Grid *grid_create_from_file(const char *path);

/* Menghapus grid (free semua memory yang dialokasikan). */
void grid_destroy(Grid *g);

/* Cetak grid ke stdout. */
void grid_print(Grid *g);

/* Ambil karakter pada koordinat (r,c) */
char grid_get(Grid *g, int r, int c);

/* Set obstacle pada koordinat tertentu (menulis '1'). */
void grid_set_obstacle(Grid *g, int r, int c);

/* Cari posisi Start 'S' dan Goal 'G'. Mengembalikan 0 jika keduanya ditemukan. */
int grid_find_start_goal(Grid *g, int *sr, int *sc, int *gr, int *gc);

/* Buat salinan (deep copy) grid untuk keperluan visualisasi. */
Grid* grid_clone(const Grid *src);

#endif // GRID_H
