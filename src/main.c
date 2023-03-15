#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
# define buffer_size 1000
char current_line[buffer_size]; // search_res.log
char filename_last[buffer_size]; //current for future use 
char current_line_num[buffer_size];
int first_colon_len=0;
int line_int=0;
bool exit_loop=false;
enum op {
    exit_switch,
    skip,
    delete_single,
    vim,
    delete_multiple,
    First = exit_switch,
    Last = delete_multiple,
    
};
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
        fprintf(fp,"%c",current_line[i]);
    }
    fprintf(fp,"\n");
}
void print_deleteList(FILE *fp,int st_line, int end_line){
    fprintf(fp, "sed -i '%d,%dd' ", st_line,end_line);
    for(int i=0;i<first_colon_len-1;i++){
        fprintf(fp,"%c",current_line[i]);
    }
    fprintf(fp,"\n");
}
void switch_input(FILE *fp_d, int* line_delta){
        int operation=0;
        int st_line,end_line;
        while( 1 ){
            printf("\033[1mPlease enter your operation choice:  ");    //bold
            printf("\033[0m\n");//black
            printf("%d for [EXIT and Flush];\n",exit_switch); 
            printf("%d for [SKIP this line]\n",skip); 
            printf("%d for [DELETE single line]\n",delete_single); 
            printf("%d for [Vim]\n",vim);
            printf("%d for [DELETE Mul lines]",delete_multiple);
            printf("     INPUT[0-%d]:",Last); 
            scanf("%d",&operation);
            switch (operation) { 
                case delete_multiple: 
                    printf("\033[31m[DELETE Mul lines] Well received!\n"); //red
                    printf("\033[0m\n");//black
                    printf("\033[1mPlease enter the start line for deletion:\n");
                    scanf("%d",&st_line);
                    printf("\033[1mPlease enter the last line for deletion:");
                    printf("\033[0m\n");//black
                    scanf("%d",&end_line);
                    *line_delta+=(end_line-st_line+1);
                    printf("\033[32mDelete multiple lines is asynchronous, flushing and reloading by design!\n"); //green
                    printf("\033[0m\n");//black
                    printf("Please wait until the program is reloading and processing the deletion thanks! \nInput ANY character to confirm acknowledge: ");//black
                    char temp[buffer_size];
                    scanf("%s",temp);
                case exit_switch:
                    printf("\033[32m[EXIT and Flush] Well received!\n"); //green
                    printf("\033[0m\n");//black
                    exit_loop=true;
                    break;
                case skip: 
                    printf("\033[32m[SKIP] Well received!\n"); //green
                    printf("\033[0m\n"); //black
                    break;
                case delete_single:
                    printf("\033[31m[DELETE single line] Well received!\n"); //red
                    printf("\033[0m\n");//black
                    print_singledeleteList(fp_d,line_int-*line_delta);
                    *line_delta+=1;
                    break;
                case vim:
                    printf("\033[32m[Vim] Well received!\n"); //red
                    printf("\033[0m\n");//black
                    pid_t childPid = fork();
                    int status;
                    if (childPid) {      
                    }
                    else {
                        char filename_current_full[buffer_size]="./"; 
                        strcat(filename_current_full, filename_last);
                        char * path = filename_current_full;
                        char lines_temp[buffer_size]="+"; 
                        strcat(lines_temp, current_line_num);
                        char * lines_ = lines_temp;
                        execl("/usr/bin/vim","/usr/bin/vim",lines_,path,NULL);         
                    }
                    break;
                default:
                    printf("\033[33mFailure, Invalid input: %d! Please retry or exit. ",operation); //yellow
                    printf("\033[0m\n");//black
            }
            if(operation > Last || operation<First || operation== vim){
                continue;
            }
            else{
                break;
            }
    }   
}

void process_search_log(FILE *fp,FILE *fp_d){
    int lines = 0; // lines of the file
    int ch = 0;
    int loop_id=1,loop_fileid=1;
    int len = 0;//  length of line, changing from 0 - current value
    int max_len = 0;//  max length of line
    int max_file_size =0; // file length size 
    bool first_colon=true;
    bool second_colon=false;
    bool first_hit_colon=true;
    bool same_file=false;
    int line_delta=0;
    char filename_delete[buffer_size]; 
 
    printf("\033[1m--------------------------------rm id: %d file:%d--------------------------------\n",loop_id++,loop_fileid);
    printf("\033[0m\n");//black
    while((ch = fgetc(fp))!=EOF){//!
        if(ch==':'){
            if (first_colon){
                if(!first_hit_colon){
                    // printf("%d",strncmp(current_line, filename_last, len)); //debug
                   if(strncmp(current_line, filename_last, len) == 0){
                        same_file=true;
                        // printf("%d,%d",first_hit_colon,same_file); //debug
                    }
                    else{//new file
                        line_delta=0;
                        loop_id=1;
                        loop_fileid++;
                    }
                }
                else{
                    first_hit_colon=false;
                }
                strncpy(filename_last, current_line, len);

                if (first_hit_colon||!same_file){
                    printf("file name: |");
                    for(int i=0;i<len;i++){
                        printf("%c",current_line[i]);
                    }
                    printf("| (range of file name: %d)\n",len);
                }
                
                first_colon_len=len;
                first_colon_len++;
                first_colon=false;
                second_colon=true;
            }
            else if(second_colon){
                printf("line: |");
                line_int=0;
                int temp_i=0;
                for(int i=first_colon_len;i<len;i++){
                    line_int=line_int*10+current_line[i]-'0';
                    printf("%c",current_line[i]);
                    current_line_num[temp_i++]=current_line[i];
                }     
                current_line_num[temp_i++]='\0';
                printf(" %d",line_int);
                printf("| (range of len: %d-%d), \n \n",first_colon_len,len);
                second_colon=false;
                same_file=false;
            }
 
        }
        if(exit_loop){
            break;
        }
        current_line[len]=ch;
        ++len;
        if(ch == '\n'){
            for(int i=0;i<len;i++){
                printf("%c",current_line[i]);
            }  
            printf("\n");
            switch_input(fp_d, & line_delta);

            if(max_len < len)
                max_len = len;
            ++lines;
            len = 0;
            first_colon=true;
            second_colon=false;
            printf("\033[1m--------------------------------rm id: %d file:%d--------------------------------\n",loop_id++,loop_fileid);
            printf("\033[0m\n");//black
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
    FILE * fp_search= fopen("./searchLog/searchList.log","r");
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