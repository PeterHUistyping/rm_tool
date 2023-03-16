LOG_DIR=log
BUILD_DIR=build
DEL_DIR=deletedLog
searchLog_DIR=searchLog
option1=default_warning
# ./intro.sh $@
bold=$(tput bold)
normal=$(tput sgr0)
if [ -z "$1" ]
then
    echo "No argument supplied! Use ./rm.sh -h to view usage."
    exit 1
fi
if [ "$#" -eq 1 ]; then
while getopts ":hitwdec" opt; do
  case $opt in
    h)
        echo "Quick start  ./rm.sh -i (initializing & *clean*ing log)" >&2
        echo "             ./rm.sh pixel ../test [-d]" >&2
         echo "   " >&2
        echo "Usage   ./rm.sh SEARCH_WORD PATH  [-d]" >&2
        echo "           e.g. pixel     ../test [-d]" >&2
        echo "Same as ./rm.sh -w SEARCH_WORD -p PATH    [-d]" >&2
        echo "           e.g. -w pixel       -p ../test [-d]" >&2
        echo "        Optional:" >&2
        echo "                -d        together with -p -w to disable warning" >&2
         echo "   " >&2
        echo "        Others:" >&2
        echo "                -i        initialize & *clean* log " >&2
        echo "                -e        show the last time debug log " >&2
        echo "                -h        display this help and exit" >&2
        echo "                -c        clear screen" >&2
        echo "                -t NUM    for dev and test" >&2
        echo "        Choice:" >&2
        echo "                  -t 1 is -w pixel -p ../test -d" >&2
        echo "                  -t 2 is -w pixel -p ../test" >&2
        
        exit 1
    ;;
    i) 
        ./shell/init.sh
        exit 1;;
    e)
        ./shell/debug.sh
        exit 1;;
    t)
        echo Missing operand. Use ./rm.sh -h to view usage.
        exit 1;;
    c)
        clear
        exit 1;;
    w)
        echo Missing operand. Use ./rm.sh -h to view usage.
        exit 1;;
    d)
        echo Missing operand. Use ./rm.sh -h to view usage.
        exit 1;;
    \?)
      echo "Invalid option: -$OPTARG. Use ./rm.sh -h to view usage." >&2
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
    ;;   
    \?)
      echo "Invalid option: -$OPTARG. Use ./rm.sh -h to view usage." >&2
      exit 1
       
    ;;
    esac
    case $OPTARG in
        -*)
            echo "Invalid option: -$OPTARG. Use ./rm.sh -h to view usage." >&2
        exit 1
         
    ;;
    esac
done
    word=$1       
    path=$2
fi
if [ "$#" -eq 3 ]; then
    word=$1       
    path=$2
    option1=disable_warning
fi
if [ "$#" -eq 4 ]; then
while getopts ":w:p:" opt; do
    case $opt in
        w)
            word="$OPTARG" 
        ;;
         p)
            path="$OPTARG"
        ;;
        \?)
        echo "Invalid option: -$opt. Use ./rm.sh -h to view usage." >&2
        exit 1
        ;;
    esac
    case $OPTARG in
        -*)
            echo "Invalid option: -$OPTARG. Use ./rm.sh -h to view usage." >&2
        exit 1
        ;;
    esac  
done 
fi
if [ "$#" -eq 5 ]; then
while getopts ":w:p:d" opt; do
    case $opt in
        w)
            word="$OPTARG" 
        ;;
        p)
            path="$OPTARG"
        ;;
        d)  option1=disable_warning
        ;;
        \?)
        echo "Invalid option: -$opt. Use ./rm.sh -h to view usage." >&2
        exit 1
        ;;
    esac
    case $OPTARG in
        -*)
            echo "Invalid option: -$OPTARG. Use ./rm.sh -h to view usage." >&2
        exit 1
        ;;
    esac  
done 
fi

printf "%s " "--- ****** --- WELCOME to USE rm_tool 2023:) --- ****** ---"
echo 
echo Searching ${bold}{$word}${normal} in path ${bold}[$path]${normal} with ${bold}$option1${normal}
printf "%s " "Press enter to continue if the above are all correct "
read ans
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
# ack pixel ../test > ./searchLog/searchList.log

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

chmod +777 deleteList.sh
./deleteList.sh


mv searchLog/searchList.log  searchLog/searchList_`date +%Y_%m_%d_%H-%M-%S`.log
# mv deleteList.sh ./deletedLog/deleteList_`date +%Y_%m_%d_%H-%M-%S`.log
rm deleteList.sh
echo ------Deleting unused code Done!------


