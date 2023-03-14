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
mkdir deletedLog
mv deleteList.sh ./deletedLog/deleteList_`date +%Y_%m_%d_%H-%M-%S`.log
echo ------Deleting unused code Done!------
