# pragma once
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <wait.h>

#define buffer_size 1000

char current_line[buffer_size];  // search_res.log
char filename_last[buffer_size]; // current for future use
char current_line_num[buffer_size];
int first_colon_len = 0;
int line_int = 0;
bool exit_loop = false;
bool future_acknowledge = true;
// char search_path[buffer_size];
char search_ackCmd=false;
char search_ack[buffer_size];
char search_word[buffer_size];
FILE *fp_deleteLog;
void acknowledge();
bool delete_file_idChange=false;
char skip_file[buffer_size][buffer_size];
int skip_f_num=0;
void flush_delete( FILE *fp_d)
{
    acknowledge();
    fflush(fp_d);
    system("bash deleteList.sh");   
    system("echo " " > deleteList.sh");
   
    system("echo Flushed deleteList!");

    // fclose(fp);
    // fp=freopen("","w",fp);   // reopen to flush everything
    // 
    // execl("/usr/bin/bash","/usr/bin/bash","deleteList.sh",NULL);
    // execl("/usr/bin/echo","/usr/bin/echo","Hi",NULL);

    // strftime(temp, sizeof(temp), "deletedLog/deleteList_%Y-%m-%d_%H-%M-%S.log", timenow);
    // char *path = temp;
    // execl("/usr/bin/cp","/usr/bin/cp","deleteList.sh",path,NULL)
}
void flush_updateSearch(FILE *fp)
{
    fflush(fp);
    system("> searchLog/searchList.log");  
    char temp[buffer_size];
    strcpy(temp,search_ack);
    strcat(temp, " > ./searchLog/searchList.log");
    rewind(fp);
    system(temp); 
    system("echo Flushed searchList!");
}


void print_singledeleteList(FILE *fp, int st_line)
{
    fprintf(fp, "sed -i '%dd' ", st_line);
    for (int i = 0; i < first_colon_len - 1; i++)
    {
        fprintf(fp, "%c", current_line[i]);
    }
    fprintf(fp, "\n");
}

void print_deleteList(FILE *fp, int st_line, int end_line)
{
    fprintf(fp, "sed -i '%d,%dd' ", st_line, end_line);
    for (int i = 0; i < first_colon_len - 1; i++)
    {
        fprintf(fp, "%c", current_line[i]);
    }
    fprintf(fp, "\n");
}

void print_deleteFile(FILE *fp,char * filename)
{
    fprintf(fp, "sed file '%s' ", filename);
    
    fprintf(fp, "\n");
    delete_file_idChange=true;
}

void acknowledge()
{
    printf("\033[32m\nReady to Delete it!\n");        // green
    printf("\033[0mPlease wait until the program is flushing, reloading search list and processing the deletion, thanks! \n"); // black
    if (future_acknowledge)
    {
        printf("\033[0mType ANY letter to confirm acknowledge: "); // black
        char temp[buffer_size];
        scanf("%s", temp);
        printf("\033[0mInput y if you would remove future confirmation: "); // black
        scanf("%s", temp);
        if (temp[0] == 'y')
        {
            future_acknowledge = false;
        }
    }
}
