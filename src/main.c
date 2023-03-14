#include <stdio.h>
void print_deleteList(){
    FILE * fp;
    fp = fopen ("deleteList.sh", "w+");
    fprintf(fp, "sed -i '%dd' '%s'\n", 4,"test/fops.h");
    fprintf(fp, "sed -i '%d,%dd' '%s'\n", 1,2, "test/fops.c");
    fclose(fp);
}
int main(){
    print_deleteList();
   
   return(0);
}