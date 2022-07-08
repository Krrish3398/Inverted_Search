/* Documentation
Name : Sai Krishna Chaitanya V.
Date : 5th July 2022

Project : To implement Invertedd Search. The purpose of storing an index is to optimize speed and performance in
finding relevant documents for a search query. Without an index, the search
engine would scan every document in the corpus, which would require
considerable time and computing power.

Execution:.\out.exe file_1.txt file_2.txt
SUCCESS :: Inserting the file name file_1.txt into the file linked list
SUCCESS :: Inserting the file name file_2.txt into the file linked list
1. Create Database
2. Display Database
3. Update Database
4. Search Database
5. Save Database
**Enter Your Option**
1
SUCCESS :: Creation of database for file_1.txt
SUCCESS :: Creation of database for file_2.txt
Do you wish to Continue (y/n): y
2
[index]  [word]  file_count  file/s: File  file_name  word_count
[0]      [ARE]         1       file/s: File  file_2.txt  1
[7]      [Hi]         2       file/s: File  file_1.txt  3
file_2.txt  1
[7]      [HELLO]         1       file/s: File  file_1.txt  1
[7]      [HOW]         1       file/s: File  file_2.txt  1
[7]      [HI]         1       file/s: File  file_2.txt  1
[24]      [YOU]         1       file/s: File  file_2.txt  1
Do you wish to Continue (y/n): y
3
Enter the file name
file_3.txt
SUCCESS :: Inserting the file name file_3.txt into the file linked list
SUCCESS :: Creation of database for file_3.txt
Do you wish to Continue (y/n): y
2
[index]  [word]  file_count  file/s: File  file_name  word_count
[0]      [ARE]         1       file/s: File  file_2.txt  1
[7]      [Hi]         2       file/s: File  file_1.txt  3
file_2.txt  1
[7]      [HELLO]         1       file/s: File  file_1.txt  1
[7]      [HOW]         1       file/s: File  file_2.txt  1
[7]      [HI]         1       file/s: File  file_2.txt  1
[8]      [Im]         1       file/s: File  file_3.txt  1
[10]      [Krishna]         1       file/s: File  file_3.txt  1
[24]      [YOU]         1       file/s: File  file_2.txt  1
Do you wish to Continue (y/n): y
4
Enter the word to search
Im
Word Im is present in 1 file
In file : file_3.txt 1 times
Do you wish to Continue (y/n): y
5
Enter the filename
save.txt
SUCCESS :: Database is saved
Do you wish to Continue (y/n): n
*/

#include "inverted_search.h"

int main(int argc, char *argv[])
{
    // system("clear");
    int opt;
    char option;
    char word[15];
    // validating the CLA
    if (argc <= 0)
    {
        printf("FAILURE :: Enter valid number of args\nUSAGE :: ./Slist.exe file_1.txt, file_2.txt...\n");
        return FAILURE;
    }

    // create list of files
    // declare Head pointer
    Flist *f_head = NULL;

    // validating the file
    file_validation_n_file_list(&f_head, argv);
    if (f_head == NULL)
    {
        printf("INFO :: No files are available in the file linked list\nHence process terminated\n");
        return 1;
    }
    // creating a hasttable(array of structure pointers)
    // size is 27 to accomidate a to z apphabits + 1 special chars + 1 numerics
    Wlist *head[27] = {NULL};
    // Display menu
    printf("1. Create Database\n2. Display Database\n3. Update Database\n4. Search Database\n5. Save Database\n**Enter Your Option**\n");
    do
    {
        scanf("%d", &opt);
        switch (opt)
        {
        case 1:
            // create database
            create_database(f_head, head);
            break;
        case 2:
            //case for display db
            display_database(head);
            break;
        case 3:
        //case for update db
            update_database(head, &f_head);
            break;
        case 4:
            //case for search db
            printf("Enter the word to search\n");
            scanf("%s", word);
            search(head[tolower(word[0]) % 97], word);
            break;
        case 5:
            //case for save db
            save_database(head);
            break;
        default:
            printf("Invalid Option\n");
        }
        printf("Do you wish to Continue (y/n): ");
        scanf("\n%c", &option);
    } while (option == 'y');
    return SUCCESS;
}
