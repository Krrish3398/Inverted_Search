#include "inverted_search.h"

void file_validation_n_file_list(Flist **f_head, char *argv[])
{
    int count = 1, empty;
    while (argv[count] != NULL)
    {
        // condition for file not available
        empty = isFileEmpty(argv[count]);
        if (empty == FILE_NOTAVAILABLE)
        {
            printf("INFO :: File %s is not available\n", argv[count]);
            printf("Hence file %s not added to File List\n", argv[count]);
            count++;
            continue;
        }
        // condition if file is empty
        else if (empty == FILE_EMPTY)
        {
            printf("INFO :: File %s is Empty\n", argv[count]);
            printf("Hence file %s not added to File List\n", argv[count]);
            count++;
            continue;
        }
        else
        {
            // creating the list of files
            int ret_val = to_create_list_of_files(f_head, argv[count]);
            if (ret_val == SUCCESS)
            {
                printf("SUCCESS :: Inserting the file name %s into the file linked list\n", argv[count]);
            }
            else if (ret_val == REPEATATION)
            {
                printf("INFO :: file_name - %s is repeated. **Not added to Linked list\n", argv[count]);
            }
            else
            {
                printf("FAILURE\n");
            }
            count++;
        }
    }
}

int isFileEmpty(char *filename)
{
    // opening file in read mode
    FILE *fptr = fopen(filename, "r");
    // checking if file names are available or not
    if (fptr == NULL)
    {
        if (errno == ENOENT)
        {
            return FILE_NOTAVAILABLE;
        }
    }
    // checking for contents
    fseek(fptr, 0, SEEK_END);
    if (ftell(fptr) == 0)
        return FILE_EMPTY;
}
int to_create_list_of_files(Flist **f_head, char *name)
{
    static int flag = 0;
    int strcmp_val;
    if (flag >= 1)
    {

        // create local ref ptr of type Slist
        Flist *prev = *f_head;
        // traverse through the list
        while (prev != NULL)
        {
            strcmp_val = strcmp(prev->file_name, name);
            // printf("strcmp_val - %d\n", strcmp_val);
            prev = prev->link;
        }

        if (strcmp_val == 0)
        {
            return REPEATATION;
        }
    }
    flag++;
    // create node
    Flist *new = malloc(sizeof(Flist));

    // Error check if memory is allocated or not
    if (new == NULL)
    {
        return FAILURE;
    }

    // update data and link part
    strcpy(new->file_name, name);
    new->link = NULL;

    // checking whether list is empty or not
    if (*f_head == NULL)
    {
        *f_head = new;
        return SUCCESS;
    }

    // create local ref ptr of type Slist
    Flist *temp = *f_head;

    // traverse through the list
    while (temp->link != NULL)
    {
        temp = temp->link;
    }
    // establishing the link between last node and new node
    temp->link = new;
    return SUCCESS;
}