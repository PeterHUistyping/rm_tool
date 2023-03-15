LOG_DIR=log

BUILD_DIR=build

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

mkdir deletedLog

mv deleteList.sh ./deletedLog/deleteList_`date +%Y_%m_%d_%H-%M-%S`.log

echo ------Deleting unused code Done!------