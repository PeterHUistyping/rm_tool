LOG_DIR=log
BUILD_DIR=build
DEL_DIR=deletedLog
searchLog_DIR=searchLog
if ! [ -d "$searchLog_DIR" ]; then 
    mkdir searchLog 
fi
if ! [ -d "$DEL_DIR" ]; then 
    mkdir deletedLog
fi
# while :
# do
# ...
# done
ack pixel ../test > ./searchLog/searchList.log

echo ------ rm the previous build  ------
rm -rf build
mkdir build
cd build

echo ------ Start to build the rm_tool needed ------
cmake .. > CMake.log 2>&1  
echo ------ CMake detail written to: build/CMake.log ------
make > detail.log 2>&1  
echo ------ Build detail written to: build/detail.log ------
cd ..
ack pixel ../test
./build/rm_tool 
 



echo ---Starting to delete unused code---

./deleteList.sh

mv searchLog/searchList.log  searchLog/searchList_`date +%Y_%m_%d_%H-%M-%S`.log
# mv deleteList.sh ./deletedLog/deleteList_`date +%Y_%m_%d_%H-%M-%S`.log
rm deleteList.sh
echo ------Deleting unused code Done!------


