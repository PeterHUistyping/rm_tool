LOG_DIR=log
BUILD_DIR=build
DEL_DIR=deletedLog
searchLog_DIR=searchLog
option1=default_warning
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
        echo "Usage ./rm.sh -p ../test -w pixel [-d]" >&2
        echo "              -p PATH -w SEARCH_WORD [-d]" >&2
        echo "                      e.g. -p ../test -w pixel [-d]" >&2
        echo "              -d together with -p -w to disable warning" >&2
        echo "              -t NUM for dev and test" >&2
        echo "                   Choice:" >&2
        echo "                      -t 1 is -p ../test -w pixel -d" >&2
        echo "                      -t 2 is -p ../test -w pixel " >&2
        echo "              -h display this help and exit" >&2
        exit 1
    ;;
  
   
    \?)
      echo "Invalid option: -$OPTARG. Use -h to view usage." >&2
      exit 1
      ;;
  esac
done
fi
if [ "$#" -eq 2 ]; then
while getopts ":t:" opt; do
  case $opt in
    t)
        args="$OPTARG"
    ;;   
    \?)
      echo "Invalid option: -$OPTARG. Use -h to view usage." >&2
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
    echo Test $args
    case $args in 
    1)
        path=../test 
        word=pixel
        option1=disable_warning
    ;;
    2) 
        path=../test 
        word=pixel
    ;;
    esac

fi
if [ "$#" -eq 4 ]; then
while getopts ":p:w:" opt; do
    case $opt in
        p)
            path="$OPTARG"
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
if [ "$#" -eq 5 ]; then
while getopts ":p:w:d" opt; do
    case $opt in
        p)
            path="$OPTARG"
        ;;
        w)
            word="$OPTARG" 
        ;;
        d)  option1=disable_warning
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
echo searching {$word} in path [$path] with $option1

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

./build/rm_tool $path  $word    $option1
 

echo ---Starting to delete unused code---

chmod +777 deleteLish.sh
./deleteList.sh


mv searchLog/searchList.log  searchLog/searchList_`date +%Y_%m_%d_%H-%M-%S`.log
# mv deleteList.sh ./deletedLog/deleteList_`date +%Y_%m_%d_%H-%M-%S`.log
rm deleteList.sh
echo ------Deleting unused code Done!------


