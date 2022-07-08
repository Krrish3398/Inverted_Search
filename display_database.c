
#include "inverted_search.h"
void display_database(Wlist *head[])
{
    printf("[index]  [word]  file_count  file/s: File  file_name  word_count\n");

    for (int idx = 0; idx < 27; idx++)
    {
        if (head[idx] != NULL)
        {
            print_word_count(head[idx]);
        }
    }
}

int print_word_count(Wlist *head)
{
    // traverse through the Wlist
    while (head != NULL)
    {
        printf("[%d]      [%s]         %d       file/s: File  ", tolower(head->word[0]) % 97, head->word, head->file_count);
        Ltable *tHead = head->Tlink;

        // traverse through the Ltable
        while (tHead)
        {
            printf("%s  %d\n", tHead->file_name, tHead->word_count);
            tHead = tHead->table_link;
        }
        printf("\n");
        head = head->link;
    }
}