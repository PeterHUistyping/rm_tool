# pragma once
# include "common.h"

void openfile_check(FILE *fp)
{
    if (fp == NULL)
    {
        printf("Error when opening the file!\n");
        exit(1);
    }
}

void ack_searchtoFile()
{
    char cmd_temp[buffer_size] ;  
    strncpy(cmd_temp,search_ack,strlen(search_ack));
    strcat(cmd_temp, " > ./searchLog/searchList.log");
    system("echo Flushed searchList!");
    char * cmd_ack = cmd_temp;
    system(cmd_ack);
}

void welcome()
{
    printf("--- ****** --- WELCOME to USE rm_tool 2023:) --- ****** ---\n");
    printf("\n");
    int i, j;
    for (i = 1; i <= 13; i += 2)
    {
        for (j = 1; j <= i; j++)
            printf("*");
        printf("\n");
    }
    for (i = 11; i >= 1; i -= 2)
    {
        for (j = 1; j <= i; j++)
            printf("*");
        printf("\n");
    }
    printf("\n");
}

void file_data(FILE *fp)
{
    int lines = 0; // lines of the file
    int ch = 0;
    int len = 0;           //  length of line
    int max_len = 0;       //  max length of line
    int max_file_size = 0; // file length size
    while ((ch = fgetc(fp)) != EOF)
    { //!
        ++len;
        if (ch == '\n')
        {
            if (max_len < len)
                max_len = len;
            ++lines;
            len = 0;
        }
    }
    if (len)
        ++lines;
    printf("Max_len of the a line is %d \n", max_len);
    printf("Review %d searches\n", lines);
    rewind(fp);
}

void print_charArray(char * cmd_ack){
    for(int i=0;i<strlen(cmd_ack);i++){
        printf("%c",cmd_ack[i]);
    }
    printf("\n");
}