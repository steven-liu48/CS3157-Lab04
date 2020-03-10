#include "mdb.h"
#include "mylist.h"
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

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
		//printf("%d \n", counter++);
		struct MdbRec *data = pointer -> data;
		if (strstr(data -> name, string) ||strstr(data -> msg, string)){
			printf("   %d: {%s} said {%s} \n", counter, data -> name, data -> msg);
		}
		counter++;
		pointer = pointer -> next;
	}
}

void freeData(){

}

int main(int argc, char **argv)
{
	if (argc != 2) {
		fprintf(stderr, "%s\n", "usage: ncat <file_name>"); exit(1);
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
	while (scanf("%s", input) != EOF){
		//printf("%s \n", input);
		findData(input, &list);
		printf("lookup: ");
	}
	
	//Free everything
	
	//Close file and end
	fclose(fp);
	return 0;
}

