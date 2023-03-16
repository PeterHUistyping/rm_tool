# pragma once
#include "util.h"
#include "common.h"
enum op
{
    exit_switch,
    skip,
    delete_single,
    vim,
    delete_multiple,
    ack,
    linux_cmd,
    First = exit_switch,
    Last = linux_cmd,

};

void switch_input(FILE *fp, FILE *fp_d, int *line_delta)
{
    int operation = 0;
    int st_line, end_line;
    while (1)
    {
        printf("\033[1mPlease enter your operation choice:  "); // bold
        printf("\033[0m\n");                                    // black
        printf("%d [EXIT and Flush]\n", exit_switch);
        printf("%d [SKIP this line]\n", skip);
        printf("%d [DELETE single line]\n", delete_single);
        printf("%d [Vim]\n", vim);
        printf("%d [DELETE Mul lines]\n", delete_multiple);
        printf("%d [ack search]\n", ack);
        printf("%d [Any other linux command on cwd]", linux_cmd);
        printf("     INPUT[0-%d]:", Last);
        scanf("%d", &operation);
        switch (operation)
        {
        case linux_cmd:
            flush_delete(fp, fp_d, line_delta);
            printf("%s:$", "rm_tool");

            char temp[buffer_size];
            scanf("%s", temp);
            printf("\n");
            system(temp);
            printf("\n");
            break;
        case ack:
            char cmd_temp[buffer_size] = "ack ";
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
            printf("\033[31m[DELETE Mul lines] Well received!\n"); // red
            printf("\033[0m\n");                                   // black
            printf("\033[1mPlease enter the start line for deletion:\n");
            scanf("%d", &st_line);
            printf("\033[1mPlease enter the last line for deletion:");
            printf("\033[0m\n"); // black
            scanf("%d", &end_line);
            print_deleteList(fp_deleteLog, st_line, end_line);
            print_deleteList(fp_d, st_line, end_line);
            flush_delete(fp, fp_d, line_delta);
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
        case delete_single:
            printf("\033[31m[DELETE single line] Well received!\n"); // red
            printf("\033[0m\n");                                     // black
            print_singledeleteList(fp_d, line_int - *line_delta);
            print_singledeleteList(fp_deleteLog, line_int - *line_delta);
            *line_delta += 1;
            break;
        case vim:
            printf("\033[32m[Vim] Well received!\n"); // red
            printf("\033[0m\n");                      // black
            flush_delete(fp, fp_d, line_delta);
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
            char lines_temp[buffer_size] = "vim +";
            strcat(lines_temp, current_line_num);
            strcat(lines_temp, " ");
            strcat(lines_temp, filename_last);
            char *cmd = lines_temp;
            system(cmd);
            // execl("/usr/bin/vim","/usr/bin/vim",lines_,path,NULL);
            //}
            break;

        default:
            printf("\033[33mFailure, Invalid input: %d! Please retry or exit. ", operation); // yellow
            printf("\033[0m\n");                                                             // black
        }
        if (operation > Last || operation < First || operation == vim || operation == ack || operation == delete_multiple || operation == linux_cmd)
        {
            continue;
        }
        else
        {
            break;
        }
    }
}

