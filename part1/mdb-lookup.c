#include "mdb.h"
#include "mylist.h"
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Node *appendNode(struct List *list, struct MdbRec *data){
	struct Node *pointer = list -> head;
	if(!pointer){
        return addFront(list, data);
    }
	while(pointer -> next != NULL){
		pointer = pointer -> next;
	}
	return addAfter(list, pointer, data);
}

void findData(char *string, struct List *list){
	struct Node *pointer = list -> head;
	int counter = 1;
	while (pointer != NULL){
		struct MdbRec *data = pointer -> data;
		//printf("%d%d ", strstr(data -> name, string) != NULL, strstr(data -> msg, string) != NULL);
		//printf("%s %s %s \n", data->name, data->msg, string);
		if (strstr(data -> name, string) ||strstr(data -> msg, string)){
			if (counter < 10) printf("   ");
			if (counter < 100 && counter >=10) printf("  ");
			if (counter >= 100) printf(" ");
			printf("%d: {%s} said {%s} \n", counter, data -> name, data -> msg);
		}
		counter++;
		pointer = pointer -> next;
	}
}

void freeData(struct List *list){
	struct Node *pointer = list -> head;
	while (pointer != NULL){
        //struct Node *pointer = list -> head;
		free(pointer -> data);
		pointer = pointer -> next;
	}
}

int main(int argc, char **argv)
{
	//Make sure a file name is provided and valid. Open file
	if (argc != 2) {
		fprintf(stderr, "%s\n", "usage: ncat <file_name>"); 
		exit(1);
	}
	char *filename = argv[1];
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror(filename);
        exit(1);
	}

	//Create & Initialize a list
	struct List list;
	initList(&list);
    
	//Read data into the list
    while (1){
		struct MdbRec *buffer = malloc(40);
		if (fread(buffer, 40, 1, fp) == 1){
			printf("%s ", buffer -> name);
	        printf("%s \n", buffer -> msg);
			appendNode(&list, buffer);
		}else{
			break;
		}
    }
	
	//Take in user input and look for it
	printf("lookup: ");
	char input[1000];
	while (fgets (input, 1000, stdin) != NULL){
		char *proc = malloc(6);
		strncpy(proc, input, 5);
		for(int i=0; i<5; i++){
			if(!isprint(proc[i])){
				proc[i] = '\0';
			}
		}
		findData(proc, &list);
		free(proc);
		printf("\nlookup: ");
	}
	
	//Free everything
	freeData(list);
	while ((popFront(&list)) != NULL) {
        ;
    }

	//Close file and end
	fclose(fp);
	return 0;
}

