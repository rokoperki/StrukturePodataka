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
int insert_after(positon previous, positon to_insert);
positon find_last(positon head);
positon find_by_lname(positon first, char* lname);
int delete_person(positon head, positon to_delete);
int insert_before(positon next, positon to_insert, positon head);
int sort_by_lname(positon head);
int save_list_to_file(positon first, char* filename);
int read_list_from_file(positon first, char* filename);

int main()
{
    person head = {.fname = "", .lname = "", .birth_year = 0, .next = NULL};
    prepend_list(&head, "Jane", "Doe", 1990);
    prepend_list(&head, "John", "Janice", 1991);
    append_list(&head, "Jack", "Jacky", 1992);
    print_list(&head);

    positon jane = find_by_lname(&head, "Doe");
    printf("Found: %s %s\n", jane->fname, jane->lname);

    printf("Deleting Jane\n");
    delete_person(&head, jane);
    print_list(&head);

    printf("Inserting new person after Jack\n");
    positon jack = find_by_lname(&head, "Jacky");
    positon new_person = create_person("Jill", "Doe", 1993);
    insert_after(jack, new_person);
    print_list(&head);
    
    printf("Inserting new person before Jack\n");
    new_person = create_person("Mate", "Mates", 1993);
    insert_before(jack, new_person, &head);
    print_list(&head);

    printf("Sorting by last name\n");
    sort_by_lname(&head);
    print_list(&head);

    printf("Saving list to file\n");
    save_list_to_file(&head, "zad2.txt");

    person headFile = {.fname = "", .lname = "", .birth_year = 0, .next = NULL};
    read_list_from_file(&headFile, "zad2.txt");
    printf("Reading list from file\n");
    print_list(&headFile);

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

int insert_after(positon previous, positon to_insert)
{
    to_insert->next = previous->next;
    previous->next = to_insert;

    return 0;
}

int insert_before(positon next, positon to_insert, positon head)
{
    positon temp = head;
    while (temp->next != next)
    {
        temp = temp->next;
    }

    temp->next = to_insert;
    to_insert->next = next;

    return 0;
}

int sort_by_lname(positon head)
{
    positon i, j;
    for (i = head->next; i->next; i = i->next)
    {
        for (j = i->next; j; j = j->next)
        {
            if (strcmp(i->lname, j->lname) > 0)
            {
                char temp[32];
                strcpy(temp, i->lname);
                strcpy(i->lname, j->lname);
                strcpy(j->lname, temp);
            }
        }
    }

    return 0;
}

int save_list_to_file(positon head, char* filename)
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

    printf("List saved to file %s\n", filename);
    fclose(file);
    return 0;   
}

int read_list_from_file(positon head, char* filename)
{
    FILE* file = fopen(filename, "r");
    if (!file)
    {
        printf("Failed to open file %s\n", filename);
        return -1;
    }

    char fname[32], lname[32];
    int birth_year;
    while (fscanf(file, "%s %s %d", fname, lname, &birth_year) == 3)
    {
        append_list(head, fname, lname, birth_year);
    }

    fclose(file);
    return 0;
}