#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct stackElement* position;

typedef struct stackElement{
    int number;
    position next;
}stackElement;

int push(position head, int number){
    position newElement = (position)malloc(sizeof(stackElement));
    if(!newElement){
        printf("Failed to allocate memory\n");
        return -1;
    }
    newElement->number = number;
    newElement->next = head->next;
    head->next = newElement;

    return 0;
}

int GetFromFile(position head, char* operation, char* filename)
{
    FILE* fp = fopen(filename, "r");
    if (!fp)
    {
        printf("Failed to open file %s\n", filename);
        return -1;
    }
	char line[256];
	while (fgets(line, sizeof(line), fp))
	{
        int number;
		int movingbyte;
		int buf_number = 0;
	
		while (true)
		{
            if(sscanf(line+buf_number, "%d %n", &number, &movingbyte) == 1){
                push(head, number);
                buf_number += movingbyte;
            }
            else{
                sscanf(line+buf_number, "%c%n", operation, &movingbyte);
                break;
            }
		}
	
		fclose(fp);
		return EXIT_SUCCESS;
	}
	return 0;
}

int printListReverse(position head){
    if(head->next){
        printListReverse(head->next);
    }
    if(head->number){
        printf("%d ", head->number);
    }

    return 0;
}

position findLast(position head){
    position temp = head;
    while(temp->next){
        temp = temp->next;
    }

    return temp;
}

int deleteBefore(position head, position element){
    position temp = head;
    while(temp->next->next != element){
        temp = temp->next;
    }
    position toDelete = temp->next;
    temp->next = temp->next->next;
    free(toDelete);

    return 0;
}

position findElementBefore(position head, position element){
    position temp = head;
    while(temp->next != element){
        temp = temp->next;
    }

    return temp;
}

int calculateStack(position head, char operation){
    position last = findLast(head);
    while(head->next != last){
        if(operation == '+'){
            last->number += findElementBefore(head, last)->number;
        }
        else if(operation == '-'){
            last->number -= findElementBefore(head, last)->number;
        }
        else if(operation == '/'){
            last->number /= findElementBefore(head, last)->number;
        }
        else if(operation == '*'){
            last->number *= findElementBefore(head, last)->number;
        }
        deleteBefore(head, last);
    }

    return 0;
}

int main(){
    stackElement head = {
        .number = 0,
        .next = NULL
    };
    char operation;
    GetFromFile(&head, &operation, "postfix.txt");
    printf("Operation: %c\n", operation);
    printListReverse(&head);
    printf("\n");
    calculateStack(&head, operation);
    printListReverse(&head);
    
    return 0;
}