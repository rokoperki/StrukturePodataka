#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct _element* position;

typedef struct _element
{
	int koef,exp;
	position next;

} element;

int InsertSortedToList(position head, position NextEl);
int InsertAfter(position head, position NextEl);
int DeleteAfter(position Element);
position InsertNew(int koef,int exp);
int GetFromFile(position head,FILE* fp);
int print_list(position first);
int SumNumbers(position head1, position head2,position zbroj);
int MultiplyNumbers(position head1, position head2, position headMultiply);
int lenghtOfList(position ptr);
int inserToTheEnd(position head, position NextEl);
int main()
{
	element head = {
		.koef=0,
		.exp=0,
		.next = NULL
	};
	element head1 =
	{
		.koef = 0,
		.exp = 0,
		.next = NULL
	};
	element Zbroj =
	{
		.koef = 0,
		.exp = 0,
		.next = NULL
	};
	element Produkt =
	{
		.koef = 0,
		.exp = 0,
		.next = NULL
	};
	FILE* fp = fopen("numbers.txt", "r");
	FILE* fp1 = fopen("numbers2.txt", "r");


	GetFromFile(&head,fp);
	GetFromFile(&head1, fp1);
	print_list(&head);
	printf("\n");
	print_list(&head1);
	SumNumbers(&head, &head1, &Zbroj);
	printf("\n");
    printf("zbroj\n");
	print_list(&Zbroj);
	MultiplyNumbers(&head, &head1, &Produkt);
	printf("\n");
    printf("umnozak\n");
	print_list(&Produkt);
	return 0;
}



position InsertNew(int koef,int exp)
{
	position NewEl=(position)malloc(sizeof(element));
	if (!NewEl)
	{
		printf("failed to find memory for new person\n");
	}
	NewEl->koef = koef;
	NewEl->exp = exp;
	NewEl->next = NULL;
	return NewEl;
}



int InsertSortedToList(position head, position NextEl)
{
	position temp = head;
	if (!NextEl)
	{
		printf("failed to allocate memory \n");
	}
	while (temp->next!=NULL && (temp->next->exp < NextEl->exp))
	{
		temp = temp->next;
	}
	
	if (temp->next == NULL || temp->next->exp > NextEl->exp)
	{
		InsertAfter(temp, NextEl);
	}
	else if(temp->next->exp==NextEl->exp)
	{
		int Sumexp = 0;
		Sumexp = temp->next->exp + NextEl->exp;
		if (Sumexp == 0)
		{
			DeleteAfter(temp);
		}free(NextEl);
		
	}
	else
	{
		InsertAfter(temp, NextEl);
	}

	return EXIT_SUCCESS;
}

int InsertAfter(position temp ,position NextEl)
{
	NextEl->next = temp->next;
	temp->next = NextEl;

    return 0;
}


int GetFromFile(position head,FILE* fp)
{
	if (!fp)
	{
		printf("mistake loading the document\n");
		return 1;
	}
	char line[256];
	while (fgets(line, sizeof(line), fp))
	{
		int koef;
		int exp;
		int movingbyte;
		int buf_number = 0;
		
	
		while (sscanf(line+buf_number, "%d %d%n", &koef, &exp, &movingbyte) == 2)
		{
			InsertSortedToList(head, InsertNew(koef, exp));
			buf_number += movingbyte;
		}
	
		fclose(fp);
		return EXIT_SUCCESS;
	}
	return 0;
}
int print_list(position head)
{
	position temp = head->next;

	while (temp)
	{
		printf("number:koef %d exp %d \n", temp->koef,temp->exp);
		temp = temp->next;
	}

	return 0;
}

int DeleteAfter(position Element)
{
	position temp = Element->next;
	Element->next = Element->next->next;
	free(temp);

    return 0;
}

int inserToTheEnd(position head, position NextEl)
{
    position temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    InsertAfter(temp, NextEl);
    return 0;
}

int SumNumbers(position head1, position head2,position zbroj)
{
    position temp1 = head1->next;
    position temp2 = head2->next;

	while (temp1 != NULL && temp2 != NULL) {
		if (temp1->exp == temp2->exp) {
			int sum = temp1->koef + temp2->koef;
			if (sum != 0) {
				inserToTheEnd(zbroj, InsertNew(sum, temp1->exp));
				temp1 = temp1->next;
				temp2 = temp2->next;
			}
		}
		else if (temp1->exp < temp2->exp) {
			inserToTheEnd(zbroj, InsertNew(temp2->koef, temp2->exp));
				temp1 = temp1->next;
				temp2 = temp2->next;
		}
		else if (temp1->exp > temp2->exp) {
			inserToTheEnd(zbroj, InsertNew(temp1->koef, temp1->exp));
				temp1 = temp1->next;
				temp2 = temp2->next;
		}

	}
	return 0;
	
}

int lenghtOfList(position ptr) {
	int len = 0;
    ptr = ptr->next;
	while (ptr != NULL) {
		len++;
		ptr = ptr->next;
	}
	return len;
}

int MultiplyNumbers(position head1, position head2, position headMultiply) {

	int maxLen = 0;
    position temp1 = head1->next;
    position temp2 = head2->next;
    
	if (lenghtOfList(head1) >= lenghtOfList(head2)) {
		maxLen = lenghtOfList(head1);
	}
	else {
		maxLen = lenghtOfList(head2);
	}

	while (maxLen != 0) {
		if (temp1 == NULL) {
			inserToTheEnd(headMultiply, InsertNew(temp2->koef, temp2->exp));
			temp2 = temp2->next;
			maxLen--;
		}
		else if (temp2 == NULL) {
			inserToTheEnd(headMultiply, InsertNew(head1->koef, head1->exp));
			temp1 = temp1->next;
			maxLen--;
		}
		else {
			headMultiply->koef = temp1->koef * temp2->koef;
			headMultiply->exp = temp1->exp + temp2->exp;
			inserToTheEnd(headMultiply, InsertNew(headMultiply->koef, headMultiply->exp));
			temp1 = temp1->next;
			temp2 = temp2->next;
			maxLen--;
		}

	}

	return 0;
}