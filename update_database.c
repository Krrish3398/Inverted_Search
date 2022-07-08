#include "inverted_search.h"
void update_database(Wlist *head[], Flist **f_head)
{
    // prompt the user to enter the file name
    char file_name[FNAME_SIZE];

    printf("Enter the file name\n");
    scanf("%s", file_name);

    // validate the file name
    int empty;
    // condition for file not available
    empty = isFileEmpty(file_name);
    if (empty == FILE_NOTAVAILABLE)
    {
        printf("INFO :: File %s is not available\n", file_name);
        printf("Hence file %s not added to File List\n", file_name);
    }
    // condition if file is empty
    else if (empty == FILE_EMPTY)
    {
        printf("INFO :: File %s is Empty\n", file_name);
        printf("Hence file %s not added to File List\n", file_name);
    }
    else
    {
        // creating the list of files
        int ret_val = to_create_list_of_files(f_head, file_name);
        if (ret_val == SUCCESS)
        {
            printf("SUCCESS :: Inserting the file name %s into the file linked list\n", file_name);
        }
        else if (ret_val == REPEATATION)
        {
            printf("INFO :: file_name - %s is repeated. **Not added to Linked list\n", file_name);
        }
        else
        {
            printf("FAILURE\n");
        }
    }
    while (*f_head)
    {
        if (!(strcmp((*f_head)->file_name, file_name)))
        {
            create_database(*f_head, head);
        }
        *f_head = (*f_head)->link;
    }
}
