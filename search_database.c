#include "inverted_search.h"
void search(Wlist *head, char *word)
{
    // check Wlist is empty or not
    if (head == NULL)
    {
        printf("INFO :: Search word is not available as WList is empty");
        return;
    }
    // if Wlist not empty traversing through the list
    while (head)
    {
        // compare the search word with  available words
        if (!strcmp(head->word, word))
        {
            printf("Word %s is present in %d file\n", word, head->file_count);
            Ltable *tHead = head->Tlink;

            while (tHead)
            {
                printf("In file : %s %d times\n", tHead->file_name, tHead->word_count);
                tHead = tHead->table_link;
            }
            printf("\n");
            return;
        }
        head = head->link;
    }
    printf("INFO :: Search word not found in the list");
}