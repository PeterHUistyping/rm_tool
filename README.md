# rm_tool Linxu
Integration of search, view and delete using ack, vim and sed.
## Pipeline
ack > search_res.log

src/main.c process the log (read and rm)

remove specific lines using Linux system call.

sed -i '4d' 'test/fops.h'
sed -i '1,2d' 'test/fops.c'

generate deletedLog with timestamp.

## Choice：
1. rm function
2. rm variable/single line