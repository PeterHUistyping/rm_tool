# rm_tool Linxu
Integration of search, view and delete using ack, vim and sed.
![del_single](./del_single.png)
## Pipeline
ack > search_res.log

src/main.c process the log (read and rm)

remove specific lines using Linux system call.

sed -i '4d' 'test/fops.h'
sed -i '1,2d' 'test/fops.c'

generate deletedLog with timestamp.

## Choice：

1. rm variable/single line
2. rm specific lines
3. rm function