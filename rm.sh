LOG_DIR=log
BUILD_DIR=build
DEL_DIR=deletedLog
if ! [ -d "$LOG_DIR" ]; then 
    mkdir log 
fi

ack pixel ./test  
ack pixel ./test > ./log/search_res.log

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
mv searchLog/search_res.log  searchLog/searchList_`date +%Y_%m_%d_%H-%M-%S`.log
mv deleteList.sh ./deletedLog/deleteList_`date +%Y_%m_%d_%H-%M-%S`.log
echo ------Deleting unused code Done!------