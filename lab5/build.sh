cd build
cmake ..
make

echo -e "\n>> Project build done!"
echo -e "\n>> KMP and naive algorythms testing starting...\n"
./SubstrSrchTest
echo -e "\n>> Cycle Shift testing starting...\n"
./ShiftTest
echo -e "\n>> Compare KMP and naive algorythms starting..."
./CheckOperations
cd ..
cd src
chmod +x clean.sh
cp clean.sh ../build
