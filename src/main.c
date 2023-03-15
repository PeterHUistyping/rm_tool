#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
char filename[1000]; // search_res.log
char filename_last[1000];
void file_data(FILE *fp){
    int lines = 0; // lines of the file
    int ch = 0;
    int len = 0;//  length of line
    int max_len = 0;//  max length of line
    int max_file_size =0; // file length size 
    while((ch = fgetc(fp))!=EOF){//!
        ++len;
        if(ch == '\n'){
            if(max_len < len)
                max_len = len;
            ++lines;
            len = 0;
        }
    }
    if(len)
        ++lines;
    printf("Lines of the file: %d \n",lines);
    printf("Max_len: %d \n",max_len);
    rewind(fp);
}
void print_deleteList(){
    FILE * fp;
    fp = fopen ("deleteList.sh", "w+");
    fprintf(fp, "# The below shell commands will be run by linux bash and stored as log.\n");
    fprintf(fp, "sed -i '%dd' '%s'\n", 4,"test/fops.h");
    fprintf(fp, "sed -i '%d,%dd' '%s'\n", 1,2, "test/fops.c");
    fclose(fp);
}

void process_search_log(FILE *fp){
    int lines = 0; // lines of the file
    int ch = 0;
    int loop_id=1;
    int len = 0;//  length of line, changing from 0 - current value
    int max_len = 0;//  max length of line
    int max_file_size =0; // file length size 
    bool first_colon=true;
    bool second_colon=false;
    bool first_hit_colon=true;
    bool exit=false;
    int first_colon_len=0;
    bool same_file=false;
    int operation;
    printf("----------------rm id: %d----------------\n",loop_id++);
    while((ch = fgetc(fp))!=EOF){//!
        if(ch==':'){
            if (first_colon){
                if(!first_hit_colon){
                    // printf("%d",strncmp(filename, filename_last, len)); //debug
                   if(strncmp(filename, filename_last, len) == 0){
                        same_file=true;
                        // printf("%d,%d",first_hit_colon,same_file); //debug
                    }
                }
                else{
                    first_hit_colon=false;
                }
                strncpy(filename_last, filename, len);
                
                if (first_hit_colon||!same_file){
                    printf("file name: |");
                    for(int i=0;i<len;i++){
                        printf("%c",filename[i]);
                    }
                    printf("| (range of file name: %d)\n ",len);
                }
                
                first_colon_len=len;
                first_colon_len++;
                first_colon=false;
                second_colon=true;
                 
            }
            else if(second_colon){
                printf("line: |");
                for(int i=first_colon_len;i<len;i++){
                    printf("%c",filename[i]);
                }     
                printf("| (range of len: %d-%d), \n \n",first_colon_len,len);
                second_colon=false;
                same_file=false;
                while( 1 ){
                    printf("Please enter your operation choice: 2 for [DELETE] and 1 for [NOT]. 0 for[exit] \n");    
                    scanf("%d",&operation);
                    if (operation == 1){
                        printf("[NOT] Valid input, well received!\n");
                        break;
                    }    
                    if (operation==2){
                        printf("[DELETE] Valid input, well received!\n");
                        break;
                    }    
                    if (operation==0){
                        printf("[EXIT] Valid input, well received!\n");
                        exit=true;
                        break;
                    }    
                    else if(operation != 2 && operation!=1 && operation!=0){
                        printf("Failure, invalid input %d\n",operation);
                        continue;
                    }
                }   
            }
        }
        if(exit){
            break;
        }
        filename[len]=ch;
        ++len;
        if(ch == '\n'){
            if(max_len < len)
                max_len = len;
            ++lines;
            len = 0;
            first_colon=true;
            second_colon=false;
            printf("---rm id: %d---\n",loop_id++);
        }
    }
    if(len)
        ++lines;
    printf("Lines of the file: %d \n",lines);
    printf("Max_len: %d \n",max_len);
    rewind(fp);
}
void open_search(FILE *fp){
     fp= fopen("./log/search_res.log","r");
     if(fp == NULL)
    {
      printf("Error when opening the file!\n");   
      exit(1);             
    }
}
void open_deleteList(FILE *fp){
    fp = fopen ("deleteList.sh", "w+");
    if(fp == NULL)
    {
      printf("Error when opening the file!\n");   
      exit(1);             
    }
    fprintf(fp, "# The below shell commands will be run by linux bash and stored as log.\n");
}
int main(){
    FILE *fp_search;
    FILE * fp_deleteList;
    printf("------WELCOME to USE rm_tool 2023!------\n");   
    open_search(fp_search);
    open_deleteList(fp_deleteList);

    file_data(fp_search);
    process_search_log(fp_search);
    fclose(fp_search);  
    fclose(fp_deleteList);
    // print_deleteList();
   return(0);
}