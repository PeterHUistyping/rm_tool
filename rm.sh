LOG_DIR=log
BUILD_DIR=build
DEL_DIR=deletedLog
searchLog_DIR=searchLog
if ! [ -d "$searchLog_DIR" ]; then 
    mkdir searchLog 
fi

ack pixel ./test  
ack pixel ./test > ./searchLog/searchList.log

echo ------ rm the previous build  ------
rm -rf build
mkdir build
cd build

echo ------ Start to build the rm_tool needed ------
cmake ..
make
cp rm_tool ../rm_tool
cd ..


./rm_tool


echo ---Starting to delete unused code---

./deleteList.sh


if ! [ -d "$DEL_DIR" ]; then 
    mkdir deletedLog
fi
mv searchLog/searchList.log  searchLog/searchList_`date +%Y_%m_%d_%H-%M-%S`.log
mv deleteList.sh ./deletedLog/deleteList_`date +%Y_%m_%d_%H-%M-%S`.log
echo ------Deleting unused code Done!------