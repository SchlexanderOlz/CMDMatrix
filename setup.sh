echo "[*] Creating build directory"
mkdir build
cd build
echo "[*] Seting up dependencies"
cmake ..
echo "[*] Building matrix"
make
echo "[*] Executing..."
./matrix