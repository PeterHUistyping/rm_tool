#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <wait.h>
# define buffer_size 1000
char current_line[buffer_size]; // search_res.log
char filename_last[buffer_size]; //current for future use 
char current_line_num[buffer_size];
int first_colon_len=0;
int line_int=0;
bool exit_loop=false;
bool future_acknowledge=true;
char search_path[buffer_size];
char search_word[buffer_size];
FILE *fp_deleteLog;
enum op {
    exit_switch,
    skip,
    delete_single,
    vim,
    delete_multiple,
    ack,
    First = exit_switch,
    Last = ack,
    
};
void openfile_check(FILE *fp){
     if(fp == NULL)
    {
      printf("Error when opening the file!\n");   
      exit(1);             
    }
}
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
    printf("Max_len of the a line is %d \n",max_len);
    printf("Review %d searches\n",lines);
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
void acknowledge(){
    printf("\033[32mDelete multiple lines is asynchronous, flushing and reloading by design!\n"); //green
    printf("\033[0mPlease wait until the program is reloading and processing the deletion, thanks! \n");//black
    if(future_acknowledge){
        printf("\033[0mInput ANY character to confirm acknowledge: ");//black
        char temp[buffer_size];
        scanf("%s",temp);
        printf("\033[0mInput y if you would remove future confirmation: ");//black
        scanf("%s",temp);
        if(temp[0]=='y'){
            future_acknowledge=false;
        }
    }
    
}
void flush_delete(FILE *fp,FILE *fp_d,int* line_delta){
    acknowledge();
    fflush(fp_d);
    fflush(fp);
    
    system("bash deleteList.sh");  
    system("echo # flushed > deleteList.sh");  
    system("> searchLog/searchList.log");   
    char cmd_temp[buffer_size]="ack "; 
    strcat(cmd_temp, search_word);
    strcat(cmd_temp, " ");
    strcat(cmd_temp, search_path);
    strcat(cmd_temp, " > ./searchLog/searchList.log");
    char *cmd_ack = cmd_temp;                 
    system(cmd_ack);     
    // system("ack pixel ../test > ");   
    *line_delta=0;
    system("echo Flushed!");  
    fp=freopen("","w",fp);   // reopen to flush everything
    rewind(fp);   
    //execl("/usr/bin/bash","/usr/bin/bash","deleteList.sh",NULL);
    //execl("/usr/bin/echo","/usr/bin/echo","Hi",NULL);  
    
    // strftime(temp, sizeof(temp), "deletedLog/deleteList_%Y-%m-%d_%H-%M-%S.log", timenow);  
    // char *path = temp; 
    // execl("/usr/bin/cp","/usr/bin/cp","deleteList.sh",path,NULL)
}
 
void switch_input(FILE *fp,FILE *fp_d, int* line_delta){
        int operation=0;
        int st_line,end_line;
        while( 1 ){
            printf("\033[1mPlease enter your operation choice:  ");    //bold
            printf("\033[0m\n");//black
            printf("%d [EXIT and Flush]\n",exit_switch); 
            printf("%d [SKIP this line]\n",skip); 
            printf("%d [DELETE single line]\n",delete_single); 
            printf("%d [Vim]\n",vim);
            printf("%d [DELETE Mul lines]\n",delete_multiple);
            printf("%d [ack search]",ack);
            printf("     INPUT[0-%d]:",Last); 
            scanf("%d",&operation);
            switch (operation) { 
                case ack:
                    char cmd_temp[buffer_size]="ack "; 
                    strcat(cmd_temp, search_word);
                    strcat(cmd_temp, " ");
                    strcat(cmd_temp, search_path);
                    char *cmd_ack = cmd_temp;
                    // for(int i=0;i<strlen(cmd_ack);i++){
                    //     printf("%c",cmd_ack[i]);
                    // }
                    system(cmd_ack);    
                    break;
                case delete_multiple: 
                    printf("\033[31m[DELETE Mul lines] Well received!\n"); //red
                    printf("\033[0m\n");//black
                    printf("\033[1mPlease enter the start line for deletion:\n");
                    scanf("%d",&st_line);
                    printf("\033[1mPlease enter the last line for deletion:");
                    printf("\033[0m\n");//black
                    scanf("%d",&end_line);
                    print_deleteList(fp_deleteLog,st_line,end_line);
                    print_deleteList(fp_d,st_line,end_line);
                    flush_delete(fp,fp_d,line_delta);
                    break;
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
                    print_singledeleteList(fp_deleteLog,line_int-*line_delta);
                    *line_delta+=1;
                    break;
                case vim:
                    printf("\033[32m[Vim] Well received!\n"); //red
                    printf("\033[0m\n");//black
                    
                    int status;
                    flush_delete(fp,fp_d,line_delta);
                    //pid_t childPid = fork();
                    //if (childPid) {
                    //}
                    //else {
                    //    wait(&status);          
                        // char filename_current_full[buffer_size]; 
                        // filename_current_full[0]='.'; 
                        // filename_current_full[1]='.'; 
                        // filename_current_full[2]='/'; 
                        // filename_current_full[3]='\0'; 
                        // strcat(filename_current_full, filename_last);
                        // char* path = filename_current_full;
                    char* path = filename_last;
                    char lines_temp[buffer_size]="vim +"; 
                    strcat(lines_temp, current_line_num);
                    strcat(lines_temp, " ");
                    strcat(lines_temp,filename_last );
                    char * cmd = lines_temp;
                    system(cmd);  
                        //execl("/usr/bin/vim","/usr/bin/vim",lines_,path,NULL);      
                    //}
                    break;
               
                default:
                    printf("\033[33mFailure, Invalid input: %d! Please retry or exit. ",operation); //yellow
                    printf("\033[0m\n");//black
            }
            if(operation > Last || operation<First || operation== vim || operation==ack || operation==delete_multiple){
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
                    printf("File Name: |");
                    for(int i=0;i<len;i++){
                        printf("%c",current_line[i]);
                    }
                    // printf("| (range of file name: %d)\n",len);
                    printf("|   ");
                }
                
                first_colon_len=len;
                first_colon_len++;
                first_colon=false;
                second_colon=true;
            }
            else if(second_colon){
                printf("Line: |");
                line_int=0;
                int temp_i=0;
                for(int i=first_colon_len;i<len;i++){
                    line_int=line_int*10+current_line[i]-'0';
                    printf("%c",current_line[i]);
                    current_line_num[temp_i++]=current_line[i];
                }     
                current_line_num[temp_i++]='\0';
                printf(" %d",line_int);
                // printf("| (range of len: %d-%d), \n \n",first_colon_len,len);
                printf("| \n \n");
                second_colon=false;
                same_file=false;
            }
 
        }
        current_line[len]=ch;
        ++len;
        if(ch == '\n'){
            for(int i=0;i<len;i++){
                printf("%c",current_line[i]);
            }  
            printf("\n");
          
            switch_input(fp,fp_d, & line_delta);

            if(max_len < len)
                max_len = len;
            ++lines;
            len = 0;
            first_colon=true;
            second_colon=false;
            if(exit_loop){
                printf("Exit loop!\n");
                break;
            }
            printf("\033[1m--------------------------------rm id: %d file:%d--------------------------------\n",loop_id++,loop_fileid);
            printf("\033[0m\n");//black
            memset( current_line, '\0', sizeof(current_line) );                
        }
    }
    if(len)
        ++lines;
    
    printf("Max_len of the a line is %d \n",max_len);
    printf("Review %d searches\n",lines);
    rewind(fp);
}
void ack_searchtoFile(){
    char cmd_temp[buffer_size]="ack "; 
    strcat(cmd_temp, search_word);
    strcat(cmd_temp, " ");
    strcat(cmd_temp, search_path);
    strcat(cmd_temp, " > ./searchLog/searchList.log");
    char *cmd_ack = cmd_temp;                 
    system(cmd_ack);     
}
void welcome(){
    printf("--- ****** --- WELCOME to USE rm_tool 2023:) --- ****** ---\n");
    printf("\n");
	int i,j;
	for (i = 1; i <= 13; i+=2)
	{
		for (j = 1; j <=i; j++)
			printf("*");
		printf("\n");
	}
	for (i = 11; i>=1; i-=2)
	{
		for (j = 1; j<=i; j++)
			printf("*");
		printf("\n");
	}
    printf("\n");
}

int main(int argc, char *argv[]){
    if( argv[3][1]=='i'){
        future_acknowledge=false;
    }
    strncpy(search_path,argv[1],strlen(argv[1]));
    strncpy(search_word,argv[2],strlen(argv[2]));
    char temp[buffer_size];
    struct tm *timenow;
    time_t now = time(NULL);
    timenow = gmtime(&now);
    welcome();
    ack_searchtoFile();
    strftime(temp, sizeof(temp), "deletedLog/deleteList_%Y-%m-%d_%H-%M-%S.log", timenow);  
    char *path = temp;
    fp_deleteLog= fopen(path,"w");

    
    FILE * fp_search= fopen("searchLog/searchList.log","r+");
    FILE * fp_deleteList = fopen ("deleteList.sh", "w+");
    openfile_check(fp_search);
    openfile_check(fp_deleteList);
    openfile_check(fp_deleteLog);
    fprintf(fp_deleteList, "# The below shell commands will be run by linux bash and stored as log.\n# The line is calculated after each deletion.\n");
    fprintf(fp_deleteLog, "# The below shell commands will be run by linux bash and stored as log.\n# The line is calculated after each deletion.\n");
   

    file_data(fp_search);
    process_search_log(fp_search,fp_deleteList);
    fclose(fp_search);  
    fclose(fp_deleteList);
    fclose(fp_deleteLog);
 
    return(0);
}
