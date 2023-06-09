LOG_DIR=log
BUILD_DIR=build
DEL_DIR=deletedLog
searchLog_DIR=searchLog
option1=default_warning
ack=false
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
        echo "   " >&2

        echo "Advanced ./rm.sh SEARCH_WORD PATH [Other ack cmd] [-d]" >&2
        echo "           e.g. pixel     ../test -i [-d]" >&2
        echo "                See more using ack --help" >&2
        echo "                                   enter tool searching the keyword provided" >&2
        echo "        Optional:" >&2
        echo "                -d                 appending ack cmd to disable warning" >&2
        echo "                                   Caution: need to be the last one!" >&2
        echo "   " >&2
        
        echo "        Others:" >&2
        echo "                -i  -init          initialize & *clean* log " >&2
        echo "                -e  -error         show the last time debug log " >&2
        echo "                -h  -help          display this help and exit" >&2
        echo "                -c  -clear         clear screen" >&2
        echo "                -t NUM             for dev and test" >&2
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
    word=$1       
    path=$2
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

fi
# if [ "$#" -eq 3 ]; then
#     word=$1       
#     path=$2
#     option1=disable_warning
# fi
printf "%s " "--- ****** --- WELCOME to USE rm_tool 2023:) --- ****** ---"
echo 

if [ "$#" -ge 3 ]; then
    word=$1       
    path=$2
    # echo ${!#}
    # echo $#
    # echo ${@:$n:$#}
    case ${!#} in # last
    -d)  
        # echo -d >&2 
        option1=disable_warning
    ;;
    esac
    echo Searching via Linux command: ack ${@:1:$#-1} with ${bold}$option1${normal}
else
    echo Searching ${bold}{$word}${normal} in path ${bold}[$path]${normal} with ${bold}$option1${normal}
fi 
 



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
sudo rm -rf build
mkdir build
cd build

echo ------ Start to build the rm_tool needed ------
cmake .. > CMake.log 2>&1  
echo ------ CMake detail has been written to: build/CMake.log ------
make > detail.log 2>&1  
echo ------ Build detail has been written to: build/detail.log ------
cd ..

if [ "$#" -ge 3 ]; then  
    ./build/rm_tool ${@:1:$#-1} $option1
else
    ./build/rm_tool   $word $path    $option1
fi 

 

echo ---Starting to delete unused code---

chmod +777 deleteList.sh
./deleteList.sh

# mv searchLog/searchList.log  searchLog/searchList_`date +%Y_%m_%d_%H-%M-%S`.log
# mv deleteList.sh ./deletedLog/deleteList_`date +%Y_%m_%d_%H-%M-%S`.log
rm deleteList.sh
rm -rf searchLog
echo ------Deleting unused code Done!------


