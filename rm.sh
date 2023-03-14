rm -rf mkdir
mkdir build
cd build
cmake ..
make
cp rm_tool ../rm_tool
cd ..
./rm_tool