# rm_tool Linxu
Integration of search, view and delete using Linux System Call ack, vim and sed.
![del_single](./del_single.png)
Make use of enum, switch, file handling in C, system call.
## Pipeline
ack > search_res.log

src/main.c process the log (read and rm)

remove specific lines using Linux system call.

sed -i '4d' 'test/fops.h'
sed -i '1,2d' 'test/fops.c'

generate deletedLog with timestamp.

## Choice：
1. skip
2. rm variable/single line
3. vim
    flush -> redo ack search
4. rm specific lines
    Delete Multiple Lines is asynchronous, it will trigger flush and reload by design
5. rm function
