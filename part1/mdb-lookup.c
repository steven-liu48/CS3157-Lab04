#include "mdb.h"
#include "mylist.h"
#include <stdio.h> 
#include <stdlib.h>

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
	
	
	//Close file and end
	fclose(fp);
	return 0;
}

