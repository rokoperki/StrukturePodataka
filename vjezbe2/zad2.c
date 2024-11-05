#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _person* positon;

typedef struct _person
{
    char fname[32], lname[32];
    int birth_year;
    positon next;
} person;

positon create_person(char* fname, char* lname, int birth_year);
int prepend_list(positon head, char* fname, char* lname, int birth_year);
int append_list(positon head, char* fname, char* lname, int birth_year);
int print_list(positon first);
positon find_last(positon head);
positon find_by_lname(positon first, char* lname);
int delete_person(positon head, positon to_delete);
int insert_after(positon after, positon new_person);
positon find_before(positon head, char* lname);
int insert_before(char* lname, positon new_person, positon head);
int save_to_file(positon head, char* filename);
int read_from_file(positon head, char* filename);

int main()
{
    person head = {.fname = "", .lname = "", .birth_year = 0, .next = NULL};
    prepend_list(&head, "Mia", "Mijic", 1990);
    prepend_list(&head, "Jure", "Juric", 1991);
    append_list(&head, "Ivo", "Ivic", 1992);
    print_list(&head);

    positon jure = find_by_lname(&head, "Juric");
    printf("Found: %s %s\n", jure->fname, jure->lname);

    printf("Deleting Jure\n");
    delete_person(&head, jure);
    print_list(&head);

    printf("Inserting Mate after Mia\n");
    positon mia = find_by_lname(&head, "Mijic");
    positon mate = create_person("Mate", "Matic", 1990);
    insert_after(mia, mate);
    print_list(&head);

    positon beforeIvo = find_before(&head, "Ivic");
    positon luka = create_person("Luka", "Lukic", 1993);
    printf("Inserting Luka before Ivo\n");
    insert_before("Ivic", luka, &head);
    print_list(&head);

    save_to_file(&head, "zad2.txt");

    head.next = NULL;
    printf("Reading from file\n");
    read_from_file(&head, "zad2a.txt");
    print_list(&head);

    return 0;
}


positon create_person(char* fname, char* lname, int birth_year)
{
    positon new_person = (positon)malloc(sizeof(person));
    if (!new_person)
    {
        printf("Malloc failed in function create_person()\n");
        return NULL;
    }

    strcpy(new_person->fname, fname);
    strcpy(new_person->lname, lname);
    new_person->birth_year = birth_year;
    new_person->next = NULL;

    return new_person;
}

int prepend_list(positon head, char* fname, char* lname, int birth_year)
{
    positon new_person = create_person(fname, lname, birth_year);
    if (!new_person)
    {
        printf("Malloc failed in function create_person()\n");
        return -1;
    }

    new_person->next = head->next;
    head->next = new_person;

    return 0;
}

int append_list(positon head, char* fname, char* lname, int birth_year)
{
    positon new_person = create_person(fname, lname, birth_year);
    if (!new_person)
    {
        printf("Malloc failed in function create_person()\n");
        return -1;
    }

    positon last = find_last(head);
    last->next = new_person;

    return 0;
}

int print_list(positon first)
{
    positon temp = first->next; 

    while (temp)
    {
        printf("First name: %s Last name: %s Birth year: %d\n", temp->fname, temp->lname, temp->birth_year);
        temp = temp->next;
    }

    return 0;
}

positon find_last(positon head)
{
    positon temp = head;

    while (temp->next)
    {
        temp = temp->next;
    }

    return temp;
}

positon find_by_lname(positon first, char* lname)
{
    positon temp = first->next;

    while (temp)
    {
        if (strcmp(temp->lname, lname) == 0)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

int delete_person(positon head, positon to_delete)
{
    positon temp = head;

    while (temp->next != to_delete)
    {
        temp = temp->next;
    }

    temp->next = to_delete->next;
    free(to_delete);

    return 0;
}

int insert_after(positon after, positon new_person)
{
    new_person->next = after->next;
    after->next = new_person;

    return 0;
}

positon find_before(positon head, char* lname)
{
    positon temp = head;

    while (temp->next)
    {
        if (strcmp(temp->next->lname, lname) == 0)
        {
            return temp;
        }
        temp = temp->next;
    }

    return NULL;
}

int insert_before(char* lname, positon new_person, positon head)
{
    positon temp = find_before(head, lname);
    if (!temp)
    {
        printf("Person before last name %s not found\n", lname);
        return -1;
    }

    new_person->next = temp->next;
    temp->next = new_person;

    return 0;
}

int save_to_file(positon head, char* filename)
{
    FILE* file = fopen(filename, "w");
    if (!file)
    {
        printf("Failed to open file %s\n", filename);
        return -1;
    }
    positon temp = head->next;
    while (temp)
    {
        fprintf(file, "%s %s %d\n", temp->fname, temp->lname, temp->birth_year);
        temp = temp->next;
    }
    printf("Data saved to file %s\n", filename);
    fclose(file);
 
    return 0;
}

int read_from_file(positon head, char* filename){
    FILE* file = fopen(filename, "r");
    if (!file)
    {
        printf("Failed to open file %s\n", filename);
        return -1;
    }
    char BUFFER[150];
    while (fgets(BUFFER, sizeof(BUFFER), file))
    {
        char fname[32], lname[32];
        int birth_year;
        sscanf(BUFFER, "%s %s %d", fname, lname, &birth_year);
        append_list(head, fname, lname, birth_year);
    }

    return 0;
}

/*void sort_by_lname(positon head){
    positon current = head;
    bool swapped = true;

    if(!current->next || !current->next->next){
        return;
    }

    while (swapped)
    {
       current = head;
       swapped = false;
       while (current->next->next)
       {
            if (strcmp(current->next->lname, current->next->next->lname) > 0)
            {
                swapped = true;
                positon temp = current->next;
                current->next = current->next->next;
                temp->next = current->next->next;
                current->next->next = temp;
            }
            current = current->next;
        }
    }
}*/
