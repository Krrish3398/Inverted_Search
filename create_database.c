#include "inverted_search.h"
char *f_name;
void create_database(Flist *f_head, Wlist *head[])
{
    while (f_head)
    {
        read_datafile(head, f_head->file_name);
        f_head = f_head->link;
    }
}

Wlist *read_datafile(Wlist *head[], char *filename)
{
    f_name = filename;
    // opening file and making fptr pointing to starting index
    FILE *fptr = fopen(filename, "r");
    char word[15];
    int flag,index=0;
    // traversing through entair file and storing it in word
    while (fscanf(fptr, "%s", word) != EOF)
    {
        flag = 1;
        // calculating index position of each word
        index = tolower(word[0]) % 97;

        // for special chars and nums
        if (index > 25)
            index = 26;

        if (head[index] != NULL)
        {
            // creating local ref pointer
            Wlist *temp = head[index];
            while (temp)
            {
                if (strcmp(temp->word, word) == 0)
                {
                    update_word_count(&head[index], filename);
                    flag = 0;
                }
                temp=temp->link;
            }
        }
        if (flag == 1)
            insert_at_last(&head[index], word);
    }
    printf("SUCCESS :: Creation of database for %s\n", filename);
}

int insert_at_last(Wlist **head, data_t *data)
{
    // create node
    Wlist *new = malloc(sizeof(Wlist));

    // validation
    if (new == NULL)
    {
        return FAILURE;
    }
    // update data and link
    strcpy(new->word, data);
    new->link = NULL;
    new->file_count = 1;

    update_link_table(&new);
    // checking if list is empty or not
    if (*head == NULL)
    {
        *head = new;
        return SUCCESS;
    }
    // creating local ref pointer
    Wlist *temp = *head;
    // traversing through the list
    while (temp->link != NULL)
    {
        temp = temp->link;
    }
    temp->link = new;
    return SUCCESS;
}

int update_link_table(Wlist **head)
{
    // create node
    Ltable *Tnew = malloc(sizeof(Ltable));

    // validation
    if (Tnew == NULL)
        return FAILURE;

    // updating the data
    Tnew->word_count = 1;
    strcpy(Tnew->file_name, f_name);
    Tnew->table_link = NULL;
    (*head)->Tlink = Tnew;
    return SUCCESS;
}
int update_word_count(Wlist **head, char *filename)
{
    // create local ref for Tlink
    Ltable *temp = (*head)->Tlink;
    Ltable *prev = (*head)->Tlink;

    // compare the filenames, if file name matches increment the wordcount
    while (temp != NULL)
    {
        if (strcmp(temp->file_name, filename) == 0)
        {
            temp->word_count = temp->word_count + 1;
            return SUCCESS;
        }
        prev = temp;
        temp = temp->table_link;
    }
    // filename not matching, create link table and update the wordcount and filename

    Ltable *Tnew = malloc(sizeof(Ltable));
    if (Tnew == NULL)
    {
        return FAILURE;
    }
    Tnew->word_count = 1;
    strcpy(Tnew->file_name, filename);
    Tnew->table_link = NULL;

    prev->table_link = Tnew;

    // increment filecount in wlist
    (*head)->file_count += 1;

    return SUCCESS;
}