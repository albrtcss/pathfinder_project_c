## 2025-11-18 — Day 1: Repo init & Grid prototype (C)

**Tujuan hari ini**
- Setup project folder & git.
- Buat file header dan source untuk Grid (C).
- Buat contoh run (`run_example`) yang memuat map dan menampilkan grid.

**Pekerjaan yang dilakukan**
- Membuat struktur project:
  - src/, include/, maps/, tests/, Makefile
- Menambahkan file:
  - include/grid.h
  - src/grid.c
  - src/run_example.c
  - maps/map2.txt
- Inisialisasi git dan commit awal.

**Kode / file yang diubah**
- `include/grid.h`
- `src/grid.c`
- `src/run_example.c`
- `Makefile`

**Hasil / Output**
- Program `run_example` berhasil memuat dan menampilkan peta dari `maps/map2.txt`.

**Masalah / Bug**
- Pastikan semua baris di file peta memiliki panjang yang sama.

**Solusi / Rencana besok**
- Day 2: Implement map helper functions (get/set, find start/goal) dan console visualizer yang lebih baik.

**Waktu yang dipakai**
- ± 2 - 3 jam

## 2025-11-19 — Day 2: Map loader lengkap & console visualizer (C)

**Tujuan hari ini**
- Melengkapi fungsi loader peta (`grid_create_from_file`).
- Membuat validasi panjang baris & perbaikan memory handling.
- Menambahkan helper function seperti `grid_find_start_goal` dan `grid_set_obstacle`.
- Membuat visualizer sederhana menggunakan `grid_print`.

**Pekerjaan yang dilakukan**
- Menambahkan fungsi pembacaan file:
  - `read_line_strip_newline` untuk membaca baris tanpa `getline`.
  - Validasi semua baris map memiliki kolom yang sama.
  - Cleanup error-handling untuk mencegah memory leak.
- Menambahkan helper function:
  - `grid_set_obstacle`
  - `grid_find_start_goal`
  - final `grid_print`
- Membersihkan duplikasi fungsi `grid_print` dan memperbaiki isi `grid.h`.
- Memindahkan fungsi `main` ke `src/run_example.c`.
- Update `Makefile` untuk build yang lebih rapi.

**Kode / file yang diubah**
- `include/grid.h`
- `src/grid.c`
- `src/run_example.c`
- `Makefile`
- `maps/map1.txt`

**Hasil / Output**
- Program `run_example` berhasil:
  - Memuat peta dari `maps/map1.txt`
  - Menampilkan isi grid ke terminal
  - Menemukan posisi Start (S) dan Goal (G)

**Masalah / Bug**
- Error karena baris map tidak sama panjang → telah diperbaiki dengan validasi panjang baris.
- Duplikasi fungsi `grid_print` → sudah dibersihkan.

**Solusi / Rencana besok**
- Day 3: Mulai implementasi BFS (struktur queue, visited array, reconstruct path).

**Waktu yang dipakai**
- ± 1.5 - 3 jam

## 2025-11-20 — Day 3: BFS module setup & run_bfs (C)

**Tujuan hari ini**
- Mempersiapkan modul BFS untuk pathfinding.
- Membuat file header (`bfs.h`) dan source (`bfs.c`).
- Membuat program contoh (`run_bfs`) yang akan menjalankan BFS nanti.
- Menambahkan target baru di Makefile agar bisa menjalankan `make run_bfs`.

**Pekerjaan yang dilakukan**
- Menambahkan file baru:
  - `include/bfs.h`
  - `src/bfs.c`
  - `src/run_bfs.c`
- Update `Makefile` untuk menambahkan rule:
  - `run_bfs`
- Membuat implementasi **placeholder BFS** agar compile berjalan mulus.
- Menjalankan build testing untuk memastikan semua file terhubung dengan benar.

**Kode / file yang diubah**
- `include/bfs.h`
- `src/bfs.c`
- `src/run_bfs.c`
- `Makefile`

**Hasil / Output**
- Program `run_bfs` berhasil dikompilasi.
- BFS belum diimplementasi penuh, namun placeholder sudah berjalan tanpa error build.
- Struktur modul BFS sekarang siap untuk implementasi lengkap pada Day 4.

**Masalah / Bug**
- Compiler memberikan banyak warning karena parameter BFS belum dipakai.

**Solusi / Rencana besok**
- Gunakan `(void)param;` untuk menghilangkan warning.
- Day 4: Implementasi BFS sesungguhnya (queue, visited, parent reconstruction, dan output path).

**Waktu yang dipakai**
- ± 1 - 2 jam
