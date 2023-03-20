# pragma once
#include "util.h"
#include "common.h"
#include "operation.h"
 
void process_search_log(FILE *fp, FILE *fp_d)
{
    int lines = 0; // lines of the file
    int ch = 0;
    int loop_id = 1, loop_fileid = 1;
    int len = 0;           //  length of line, changing from 0 - current value
    int max_len = 0;       //  max length of line
    int max_file_size = 0; // file length size
    bool first_colon = true;
    bool second_colon = false;
    bool first_hit_colon = true;
    bool same_file = false;
    char filename_delete[buffer_size];
    char skip_this_file=false;
    
    while ((ch = fgetc(fp)) != EOF)
    { //!
        if (ch == ':')
        {   
            if (first_colon)
            {
                if (!first_hit_colon)
                {
                    if(skip_f_num){
                        for(int i=0;i<skip_f_num;i++){
                            // printf("%s,%s\n",current_line, skip_file[i]);
                            if(strncmp(current_line, skip_file[i], strlen(skip_file[i])) == 0 ){
                                skip_this_file=true;
                                break;
                            }
                        }
                    }

                    if (!skip_this_file&&strncmp(current_line, filename_last, len) != 0 && !delete_file_idChange)
                    {
                        bool add_new_skip=true;
                        for(int i=0;i<skip_f_num;i++){
                            if(strncmp(filename_last, skip_file[i], strlen(skip_file[i])) == 0 ){
                                    add_new_skip=false;
                                    break;
                            }
                        }

                        if(add_new_skip){
                            strncpy(skip_file[skip_f_num++], filename_last, len);   
                            printf("Update Skipped File: %s (Overall %d files)\n\n",filename_last,skip_f_num); 
                            loop_id = 1;// new file
                            loop_fileid++;
                        }

                        // printf("%d,%d",first_hit_colon,same_file); //debug
                    }
                    else
                    { 
                        delete_file_idChange=false;
                        same_file = true; 
                    }
                }
                else
                {
                    first_hit_colon = false;
                }
                memset(filename_last, '\0', sizeof(filename_last));
                strncpy(filename_last, current_line, len);
                if(!skip_this_file){
                    printf("\033[1m--------------------------------rm id: %d file:%d--------------------------------\n", loop_id++, loop_fileid);
                    printf("\033[0m\n"); // black
                }
                if (!skip_this_file &&first_hit_colon || !same_file )
                {
                     //printf("%d",skip_this_file);
                    printf("File Name: |");
                    for (int i = 0; i < len; i++)
                    {
                        printf("%c", current_line[i]);
                    }
                    // printf("| (range of file name: %d)\n",len);
                    printf("|   ");
                }

                first_colon_len = len;
                first_colon_len++;
                first_colon = false;
                second_colon = true;
            }
            else if (second_colon &&!skip_this_file)
            {
                //printf("%d",skip_this_file);
                printf("Line: |");
                line_int = 0;
                int temp_i = 0;
                for (int i = first_colon_len; i < len; i++)
                {
                    line_int = line_int * 10 + current_line[i] - '0';
                    //printf("%c", current_line[i]);
                    current_line_num[temp_i++] = current_line[i];
                    
                }
                current_line_num[temp_i++] = '\0';
                printf("%d",line_int);
                // printf("| (range of len: %d-%d), \n \n",first_colon_len,len);
                printf("| \n \n");
                second_colon = false;
                same_file = false;
            }
        }
        current_line[len] = ch;
        ++len;
        if (ch == '\n')
        {
            if(!skip_this_file){
                for (int i = 0; i < len; i++)
                {
                    printf("%c", current_line[i]);
                }
                printf("\n");
                switch_input(fp, fp_d);
            }
            

            if (max_len < len)
                max_len = len;
            ++lines;
            len = 0;
            first_colon = true;
            second_colon = false;
            if (exit_loop)
            {
                printf("Exit loop!\n");
                break;
            }
            if (delete_file_idChange)
            {
                loop_id = 1;// new file
                loop_fileid++;
            }
                               
            skip_this_file=false;
            memset(current_line, '\0', sizeof(current_line));
        }
    }
    if (len)
        ++lines;

    printf("Max_len of the a line is %d \n", max_len);
    printf("Review %d files, %d searches\n",loop_fileid, lines);
    rewind(fp);
}