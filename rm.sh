rm -rf build
mkdir build
cd build
cmake ..
make
cp rm_tool ../rm_tool
cd ..
./rm_tool
echo ---Starting to delete unused code---
./deleteList.sh
mv ./deleteList.sh ./deletedLog/
echo ------Deleting unused code Done!------
