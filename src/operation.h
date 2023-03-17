# pragma once
#include "util.h"
#include "common.h"
#include "parse.h"
enum op
{
    exit_switch,
    skip,
    delete_single,
    vim,
    delete_multiple,
    ack,
    delete_file,
    menu,
    delete_auto,
    linux_cmd,
    First = exit_switch,
    Last = linux_cmd,

};
void pr_menu(){
    printf("%d [EXIT and Flush]\n", exit_switch);
    printf("%d [SKIP this line]\n", skip);
    printf("%d [DELETE single line]\n", delete_single);
    printf("%d [Vim]\n", vim);
    printf("%d [DELETE Mul lines]\n", delete_multiple);
    printf("%d [ack search]\n", ack);
    printf("%d [DELETE current file]\n",delete_file);
    printf("%d [Menu]\n",menu);
    printf("%d [DELETE auto]\n",delete_auto);
    printf("%d [Any other linux command on cwd]", linux_cmd);
    printf("     INPUT[0-%d]:", Last);
}
void switch_input(FILE *fp, FILE *fp_d)
{
    int operation = 0;
    int st_line, end_line;
    bool first=true;
    while (1)
    {
        if(first){
            first=false;
            printf("\033[1mPlease enter your operation choice:  "); // bold
            printf("\033[0m\n");                                    // black
            pr_menu();
        }
        else{
            printf("INPUT[0-%d] Press %d for Menu:", Last,menu);
        }        
        scanf("%d", &operation);
        switch (operation)
        {
        case menu: //read 
            first=true;
            break;
        case ack: //read 
            {char cmd_temp[buffer_size]="ack ";     
            strcat(cmd_temp, search_word);
            strcat(cmd_temp, " ");
            strcat(cmd_temp, search_path);
            char *cmd_ack = cmd_temp;
            // for(int i=0;i<strlen(cmd_ack);i++){
            //     printf("%c",cmd_ack[i]);
            // }
            system(cmd_ack);}
            break;
        case vim: //read
            printf("\033[32m[Vim] Well received!\n"); // red
            printf("\033[0m\n");                      // black
            // pid_t childPid = fork();
            // if (childPid) {
            // }
            // else {
            //     wait(&status);
            //  char filename_current_full[buffer_size];
            //  filename_current_full[0]='.';
            //  filename_current_full[1]='.';
            //  filename_current_full[2]='/';
            //  filename_current_full[3]='\0';
            //  strcat(filename_current_full, filename_last);
            //  char* path = filename_current_full;
            char *path = filename_last;
            {char lines_temp[buffer_size] = "vim +";
            strcat(lines_temp, current_line_num);
            strcat(lines_temp, " ");
            strcat(lines_temp, filename_last);
            char *cmd = lines_temp;
            system(cmd);}
            // execl("/usr/bin/vim","/usr/bin/vim",lines_,path,NULL);
            //}
            break;
                case delete_file:
            {char cmd_tem[buffer_size] = "sudo rm -f ";
            strcat(cmd_tem, filename_last);
            system(cmd_tem);
            print_deleteFile(fp_deleteLog,filename_last);}
            flush_updateSearch(fp);
            break;
        case linux_cmd: //read write
            printf("rm_tool:$sudo rm -r ../test        [Example]\n");
            printf("%s:$", "rm_tool");
            char temp[buffer_size];
            int i=0;
            getchar();
            fgets(temp, sizeof(temp), stdin);
            //printf("\n");
            system(temp);
            flush_updateSearch(fp);
            //printf("\n");
            break;
        case delete_auto:
            printf("\033[31m[DELETE auto] Well received!\n"); // red
            printf("\033[0m\n");                              // black
            printf("\033[1mPlease enter either the start line of the comments above the function:");
            printf("\033[0m\n");    
            scanf("%d", &st_line);
            printf("To be deleted: \n\033[31m");
        
            // printf("\033[1mPlease enter the last line for deletion:");
            // printf("\033[0m\n"); // black
            // scanf("%d", &end_line);
            FILE *fp_auto = fopen(filename_last, "a+");
            openfile_check(fp_auto);
            end_line=parse(fp_auto,st_line);
            fclose(fp_auto);
            print_deleteList(fp_deleteLog, st_line, end_line);
            print_deleteList(fp_d, st_line, end_line);
            flush_delete(fp_d);
            flush_updateSearch(fp);
            break;
        case delete_multiple: //write
            printf("\033[31m[DELETE Mul lines] Well received!\n"); // red
            printf("\033[0m\n");                                   // black
            printf("\033[1mPlease enter the start line for deletion:\n");
            scanf("%d", &st_line);
            printf("\033[1mPlease enter the last line for deletion:");
            printf("\033[0m\n"); // black
            scanf("%d", &end_line);
            print_deleteList(fp_deleteLog, st_line, end_line);
            print_deleteList(fp_d, st_line, end_line);
            flush_delete(fp_d);
            flush_updateSearch(fp);
            break;
        case delete_single: //cache
            printf("\033[31m[DELETE single line] Well received!\n"); // red
            printf("\033[0m\n");                                     // black
            print_singledeleteList(fp_d, line_int );
            print_singledeleteList(fp_deleteLog, line_int );
            flush_delete(fp_d);
            flush_updateSearch(fp);
            break;
        case exit_switch:
            printf("\033[32m[EXIT and Flush] Well received!\n"); // green
            printf("\033[0m\n");                                 // black
            exit_loop = true;
            break;
        case skip:
            printf("\033[32m[SKIP] Well received!\n"); // green
            printf("\033[0m\n");                       // black
            break;
        default:
            printf("\033[33mFailure, Invalid input: %d! Please retry or exit. ", operation); // yellow
            printf("\033[0m\n");                                                             // black
        }

        if( operation == exit_switch || operation == skip|| operation == delete_auto ||operation == delete_single|| operation == delete_multiple||operation == delete_file)
        {
            break;
        }
        else{
            continue;
        }
    }
}

