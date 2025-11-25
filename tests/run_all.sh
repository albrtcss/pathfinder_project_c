#!/usr/bin/env bash
set -e

mkdir -p results

echo "=== RUN: run_bfs ==="
if [ -x build/run_bfs ]; then
  ./build/run_bfs | tee results/bfs_out.txt
else
  echo "build/run_bfs tidak ditemukan. Jalankan: make run_bfs"
fi

echo
echo "=== RUN: run_astar ==="
if [ -x build/run_astar ]; then
  ./build/run_astar | tee results/astar_out.txt
else
  echo "build/run_astar tidak ditemukan. Jalankan: make run_astar"
fi

echo
echo "=== RUN: visual_simple (animasi A*) ==="
if [ -x build/visual_simple ]; then
  ./build/visual_simple
else
  echo "build/visual_simple tidak ditemukan. Jalankan: make visual_simple"
fi

echo
if [ -x build/visual_ncurses ]; then
  echo "=== RUN: visual_ncurses ==="
  ./build/visual_ncurses
fi

echo
echo "Results saved to results/"
