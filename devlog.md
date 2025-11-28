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


## 2025-11-21 — Day 4: BFS Implementation Complete (C)

**Tujuan hari ini**
- Mengimplementasikan BFS pathfinding secara penuh.
- Menambahkan queue, visited, parent tracking, dan rekonstruksi jalur.
- Memperbarui `run_bfs` untuk menampilkan jalur menggunakan simbol `*`.

**Pekerjaan yang dilakukan**
- Menambahkan dan mengisi file:
  - `include/bfs.h`
  - `src/bfs.c`
  - `src/run_bfs.c`
- Mengimplementasikan BFS lengkap:
  - Struktur queue
  - visited matrix
  - parent matrix
  - Rekonstruksi path
- Menambahkan penandaan path (`*`) pada grid.
- Update Makefile untuk rule `run_bfs`.

**Kode / file yang diubah**
- `include/bfs.h`
- `src/bfs.c`
- `src/run_bfs.c`
- `Makefile`

**Hasil / Output**
- Program `run_bfs` berhasil menampilkan peta lengkap dengan jalur BFS yang telah dihitung.
- Langkah (steps) ditampilkan, posisi jalur ditandai dengan karakter `*`.

**Masalah / Bug**
- Implementasi BFS harus memastikan queue tidak overflow pada map besar.

**Solusi / Rencana besok**
- Day 5: Menambahkan visualizer animasi (frame-by-frame) untuk BFS.
- Optimisasi struktur queue agar lebih efisien.

**Waktu yang dipakai**
- ± 2 - 3 jam

## 2025-11-22 — Day 5: Implementasi A* (A-star) & Priority Queue (C)

**Tujuan hari ini**
- Mengimplementasikan algoritma A* untuk pathfinding pada grid.
- Menyediakan priority queue (binary min-heap) untuk open set.
- Menggunakan heuristic Manhattan (h = |dr| + |dc|).
- Mengukur metrik: nodes expanded, path length, dan waktu eksekusi.
- Menambahkan runner `run_astar` untuk perbandingan dengan BFS.

**Pekerjaan yang dilakukan**
- Menambahkan file:
  - `include/astar.h`
  - `src/astar.c`
  - `src/run_astar.c`
- Mengimplementasikan binary heap (min-heap) untuk open set.
- Mengimplementasikan A*:
  - g-score & f-score arrays
  - came_from (parent) array
  - open & closed sets
  - rekonstruksi path dan pengisian out_path
- Menambahkan stats output (nodes expanded, elapsed time).
- Update `Makefile` untuk menambahkan target `run_astar`.
- Menjalankan perbandingan awal antara BFS dan A* pada sample map.

**Kode / file yang diubah**
- `include/astar.h`
- `src/astar.c`
- `src/run_astar.c`
- `Makefile`

**Hasil / Output**
- A* berhasil menemukan path (jika ada) dan menandai jalur dengan `*`.
- Program menampilkan metrik: nodes expanded, path length, elapsed time.
- Perbandingan awal menunjukkan A* mengeksplorasi jumlah node lebih sedikit daripada BFS pada peta contoh.
- Contoh output yang dihasilkan:
  ```
  Map loaded:
  000000000
  0S0011000
  000011000
  0010000G0
  000000000
  Start: (1,1)
  Goal:  (3,7)

  A* Path found! Steps: 8, nodes_expanded: 12, time: 0.000000 s
  000000000
  0S**11000
  000*11000
  001****G0
  000000000
  ```

**Masalah / Bug**
- Perlu memastikan heap handling (decrease-key) benar untuk update f-score — implementasi saat ini menggunakan insert duplicates + in_closed check untuk kesederhanaan.
- Heap kapasitas harus cukup untuk ukuran map besar; reallocation sudah ditambahkan.
- Pastikan path buffer (out_path) cukup besar untuk map yang lebih luas.

**Solusi / Rencana besok**
- Day 6: Visualisasi animasi (ncurses / frame-by-frame), CI tests, dokumentasi eksperimen (graf nodes vs map size).

**Waktu yang dipakai**
- ± 3 - 5 jam

## 2025-11-25 — Day 6: Visualisasi Grid & Animasi Path (visual_simple)

**Tujuan hari ini**
- Membuat modul visualisasi sederhana (`visualize_simple`).
- Menambahkan fungsi `grid_clone()` untuk mendukung animasi path.
- Membuat file header dan source untuk visualisasi.
- Menambahkan target baru di Makefile (`visual_simple`).
- Menjalankan animasi path hasil BFS/A*.

**Pekerjaan yang dilakukan**
- Update file:
  - `include/grid.h` → menambahkan deklarasi `grid_clone()`.
  - `src/grid.c` → menambahkan implementasi lengkap `grid_clone()`.
- Membuat file baru:
  - `include/visualize_simple.h`
  - `src/visualize_simple.c`
- Menambahkan target build baru di `Makefile`:
  - `make visual_simple`
- Memastikan visualisasi berjalan dengan map ujicoba.

**Kode / file yang diubah**
- `include/grid.h`
- `src/grid.c`
- `include/visualize_simple.h`
- `src/visualize_simple.c`
- `Makefile`

**Hasil / Output**
- Program `visual_simple` berhasil menampilkan grid secara dinamis.
- Animasi path berjalan langkah demi langkah menggunakan `animate_path()`.

**Masalah / Bug**
- Error `undefined reference to WinMain` → diperbaiki dengan menambah `main()` di visualize file.
- Error `implicit declaration grid_clone` → diatasi dengan update header & include.

**Solusi / Rencana besok**
- Day 7: Implementasikan visualisasi dengan **ncurses** (`visualize_ncurses.c`).
- Tambahkan mode animasi interaktif (delay, keyboard control).
- Tambah warna & highlight start/goal/path.

**Waktu yang dipakai**
- ± 2 - 3 jam

## 2025-11-25 — Day 7: Visualisasi Terminal Menggunakan NCurses (visual_ncurses)

**Tujuan hari ini**
- Mengimplementasikan visualisasi grid menggunakan **NCurses**.
- Membuat animasi path yang lebih halus dibanding visual_simple.
- Membuat file header & source baru untuk NCurses.
- Menjalankan animasi path secara real-time di terminal.

**Pekerjaan yang dilakukan**
- Membuat file baru:
  - `include/visualize_ncurses.h`
  - `visual/visualize_ncurses.c`
- Menulis fungsi:
  - `visualize_ncurses(Grid *g, Node *path, int path_len)`
- Menambahkan logika:
  - Menggambar grid (blok, free cell, start, goal).
  - Menggambar path secara bertahap memakai loop frame.
  - Menambahkan delay frame menggunakan `usleep(120000)`.
- Menjalankan dan mengetes animasi pada grid uji coba.

**Kode / file yang diubah**
- `include/visualize_ncurses.h`
- `visual/visualize_ncurses.c`
-  update Makefile jika menambah target `visual_ncurses`.

**Hasil / Output**
- Visualisasi berjalan dalam mode NCurses:
  - Grid dan obstacle tampil dalam terminal.
  - Path muncul secara bertahap (`step-by-step animation`).
- Output akhir:
  ```
  S..##...
  ***##...
  .#****G.
  ```
  diakhiri dengan prompt **Press any key to exit...**

**Masalah / Bug**
- Error: `ncurses.h not found` pada MSYS2.
  Penyebab: Windows tidak menyediakan NCurses secara default.
- Solusi sementara: menggunakan PDCurses / memastikan paket pustaka terinstall.
- Render terminal kadang melar atau tidak rata (karakter sempit).

**Solusi / Rencana besok**
- Day 8: Menambahkan warna (COLOR_PAIR) & highlight path.
- Menambahkan menu interaktif untuk memilih delay animasi.
- Mengintegrasikan visual_ncurses ke main runner (bukan file terpisah).

**Waktu yang dipakai**
- ± 2 - 3 jam

## 2025-11-26 — Day 8: Testing & Verifikasi Output visual_simple

**Tujuan hari ini**
- Menjalankan dan menguji modul `visual_simple`.
- Memastikan pipeline A* → path → visualisasi berjalan dengan benar.
- Memverifikasi hasil pathfinding dan hasil render visual pada grid.

**Pekerjaan yang dilakukan**
- Melakukan build program dengan perintah: make visual_simple
- Menjalankan executable: ./build/visual_simple
- Memastikan seluruh proses berjalan dengan benar:
- Map berhasil dimuat.
- Titik Start dan Goal terdeteksi dengan benar.
- Algoritma A* berjalan normal dan menemukan path optimal.
- Path divisualisasikan menggunakan karakter `*` pada grid.

**Kode / file yang diubah**
- Tidak melakukan perubahan kode — hanya testing dan verifikasi.
- Makefile sudah sesuai dan tidak memerlukan update.

**Hasil / Output**
Program menghasilkan output berikut:
Map loaded:
000000000
0S0011000
000011000
0010000G0
000000000
Start: (1,1)
Goal:  (3,7)

A* Path found! Steps: 8, nodes_expanded: 12, time: 0.000000 s
000000000
0S**11000
000*11000
001****G0
000000000


**Masalah / Bug**
- Pemberian nama yang tidak konsisten sehingga menciptakan bug pada saat pemanggilan function

**Solusi / Rencana besok**
- Mulai mengerjakan integrasi visualisasi NCurses secara penuh.
- Menambahkan warna (COLOR_PAIR) dan penekanan pada path.
- Membersihkan struktur kode visualisasi dan meningkatkan fleksibilitas animasi.

**Waktu yang dipakai**
- ± 2–3 jam


