#include "util.h"
#include "operation.h"
#include "common.h"
#include "interface.h"
int main(int argc, char *argv[])
{
    if (argv[argc-1][1] == 'i')
    {
        future_acknowledge = false;
    }

    //     strncpy(search_path, argv[1], strlen(argv[1]));
    //     strncpy(search_word, argv[2], strlen(argv[2]));
    
    strncpy(search_ack,"ack ", strlen("ack "));
    bool first_ack_arg=true;
    for(int i=1;i<argc-1;i++){
        if(argv[i][0]!='-'&& first_ack_arg){
            strcat(search_word, argv[i]);
            first_ack_arg=false;
        }
        strcat(search_ack, argv[i]);
        strcat(search_ack, " ");
    }
 
    print_charArray(search_ack);
    char temp[buffer_size];
    struct tm *timenow;
    time_t now = time(NULL);
    timenow = gmtime(&now);
    welcome();
    ack_searchtoFile();
    strftime(temp, sizeof(temp), "deletedLog/deleteList_%Y-%m-%d_%H-%M-%S.log", timenow);
    char *path = temp;
    fp_deleteLog = fopen(path, "w");
 
    FILE *fp_search = fopen("searchLog/searchList.log", "r+");
    FILE *fp_deleteList = fopen("deleteList.sh", "w+");
    openfile_check(fp_search);
    openfile_check(fp_deleteList);
    openfile_check(fp_deleteLog);
    fprintf(fp_deleteList, "# The below shell commands will be run by linux bash and stored as log.\n# The line is calculated after each deletion.\n");
    fprintf(fp_deleteLog, "# The below shell commands will be run by linux bash and stored as log.\n# The line is calculated after each deletion.\n");

    file_data(fp_search);
    process_search_log(fp_search, fp_deleteList);
    fclose(fp_search);
    fclose(fp_deleteList);
    fclose(fp_deleteLog);

    return (0);
}
