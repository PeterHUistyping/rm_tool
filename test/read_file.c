#include <stdio.h>
int main(){
    FILE *fptr;
    fptr = fopen("./log/search_res.log","r");
    if(fptr == NULL)
    {
      printf("Error when opening the file!");   
      exit(1);             
    }
    fclose(fptr);
}