# pragma once
#include "util.h"
#include "common.h"
int find_start(FILE *fp,const int st_line)
{
    int lines = 0; // lines of the file
    int ch = 0;
    int len = 0;           //  length of line
    int max_len = 0;       //  max length of line
    int max_file_size = 0; // file length size
    bool start=false;
    int left=0; //{
    int right=0;//}
    while ((ch = fgetc(fp)) != EOF)
    { //!
        ++len;
        if(lines==st_line-1){
            start=true;
        }
        if(start){
            printf("%c",ch);
            if((ch==';'&& left==0&& right==0 || left==right && left!=0)){
                lines++;
                printf("\033[0m\nEnd line:");  
                printf("%d\n",lines);
                printf("left { :%d times, right { :%d times.\n",left,right);
                left=0,right=0;
                return lines;
            }
 
            else if(ch=='{'){
                left++;
            }
            else if(ch=='}'){
                right++;
            }

        }
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
int parse(FILE *fp_auto,const int st_line){
    int end_line=0;
    return find_start(fp_auto, st_line);
}
