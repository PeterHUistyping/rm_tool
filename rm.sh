LOG_DIR=log
BUILD_DIR=build
DEL_DIR=deletedLog
searchLog_DIR=searchLog

# ./intro.sh $@

if [ -z "$1" ]
then
    echo "No argument supplied! Use -h to view usage."
    exit 1
fi
if [ "$#" -eq 1 ]; then
while getopts ":h" opt; do
  case $opt in
    h)
        echo "Usage ./rm.sh -p ../test -w pixel" >&2
        echo "-h  display this help and exit" >&2
        echo "-p [path] -w [search word], e.g. -p ../test -w pixel" >&2
    ;;
    t)
        echo "-t  for dev and test" >&2
    ;;
   
    \?)
      echo "Invalid option: -$OPTARG. Use -h to view usage." >&2
      exit 1
      ;;
  esac
done
fi
if [ "$#" -eq 4 ]; then
while getopts ":p:w:" opt; do
    case $opt in
        p)
            args_1="$OPTARG"
        ;;
        w)
            word="$OPTARG" 
        ;;
        \?)
        echo "Invalid option: -$opt. Use -h to view usage." >&2
        exit 1
        ;;
    esac
    case $OPTARG in
        -*)
            echo "Invalid option: -$OPTARG. Use -h to view usage." >&2
        exit 1
        ;;
    esac
done
fi
echo searching {$word} in path [$args_1]

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
echo ------ CMake detail has been written to: build/CMake.log ------
make > detail.log 2>&1  
echo ------ Build detail has been written to: build/detail.log ------
cd ..

./build/rm_tool 
 



echo ---Starting to delete unused code---

./deleteList.sh

mv searchLog/searchList.log  searchLog/searchList_`date +%Y_%m_%d_%H-%M-%S`.log
# mv deleteList.sh ./deletedLog/deleteList_`date +%Y_%m_%d_%H-%M-%S`.log
rm deleteList.sh
echo ------Deleting unused code Done!------


