#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
char filename[1000]; // search_res.log
char filename_last[1000];
int first_colon_len=0;
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
void print_singledeleteList(FILE *fp,int st_line){
    fprintf(fp, "sed -i '%dd' ", st_line);   
    for(int i=0;i<first_colon_len-1;i++){
        fprintf(fp,"%c",filename[i]);
    }
    fprintf(fp,"\n");
}
void print_deleteList(FILE *fp,int st_line, int end_line){
    fprintf(fp, "sed -i '%d,%dd' ", st_line,end_line);
    for(int i=0;i<first_colon_len-1;i++){
        fprintf(fp,"%c",filename[i]);
    }
    fprintf(fp,"\n");
}


void process_search_log(FILE *fp,FILE *fp_d){
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
    bool same_file=false;
    int operation;

    char filename_delete[1000]; 
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
                int line_int=0;
                for(int i=first_colon_len;i<len;i++){
                    line_int=line_int*10+filename[i]-'0';
                    printf("%c %d",filename[i],line_int);
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
                        print_singledeleteList(fp_d,line_int);
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
void openfile_check(FILE *fp){
     if(fp == NULL)
    {
      printf("Error when opening the file!\n");   
      exit(1);             
    }
}
int main(){
    printf("------WELCOME to USE rm_tool 2023!------\n");   
    FILE * fp_search= fopen("./log/search_res.log","r");
    FILE * fp_deleteList = fopen ("deleteList.sh", "w+");
    openfile_check(fp_search);
    openfile_check(fp_deleteList);
    fprintf(fp_deleteList, "# The below shell commands will be run by linux bash and stored as log.\n");

    file_data(fp_search);
    process_search_log(fp_search,fp_deleteList);
    fclose(fp_search);  
    fclose(fp_deleteList);
    // print_deleteList();
   return(0);
}