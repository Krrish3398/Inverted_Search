#include "inverted_search.h"
void save_database(Wlist *head[])
{
    char file_name[FNAME_SIZE];
    // propt the user
    printf("Enter the filename\n");
    scanf("%s", file_name);
    // open the file
    FILE *fptr = fopen(file_name, "w");

    // check the word list
    for (int i = 0; i < 27; i++)
    {
        if (head[i] != NULL)
        {
            write_databasefile(head[i], fptr);
        }
    }
    fclose(fptr);
    printf("SUCCESS :: Database is saved\n");
}

void write_databasefile(Wlist *head, FILE *databasefile)
{
    while (head != NULL)
    {
        fprintf(databasefile, "#[%d]\n    word is [%s] : file count is %d : file/s: File is  ", tolower(head->word[0]) % 97, head->word, head->file_count);
        Ltable *tHead = head->Tlink;

        // traverse through the Ltable
        while (tHead)
        {
            fprintf(databasefile, "%s   word count  is   %d\n", tHead->file_name, tHead->word_count);
            tHead = tHead->table_link;
        }
        fprintf(databasefile, "\n");
        head = head->link;
    }
}