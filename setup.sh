#!/bin/bash

echo "[*] Creating build directory"
mkdir -p build/bin
cd build

if ! command -v cmake &> /dev/null; then
  echo "CMake is not installed. Please install CMake to proceed."
  exit 1
fi

echo "[*] Setting up dependencies"
cmake ..

echo "[*] Building matrix"
make

echo "[*] Executing..."
./bin/matrix
