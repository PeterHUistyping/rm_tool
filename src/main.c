#include <stdio.h>
int main(){
    FILE * fp;

   fp = fopen ("delete.sh", "w+");
   fprintf(fp, "sed -i '%dd' '%s'", 4,"test/fops.h");
   fprintf(fp, "sed -i '%d,%dd' '%s'",  1,2, "test/fops.c");
   fclose(fp);
   
   return(0);
}