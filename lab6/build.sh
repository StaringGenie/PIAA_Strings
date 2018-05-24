cd build
cmake ..
make
./AKSearchTest
./AKJokerSearchTest
cd ..
cd src
chmod +x clean.sh
cp clean.sh ../build
