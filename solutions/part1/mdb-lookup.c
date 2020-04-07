
/*
 * mdb-lookup.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mylist.h"
#include "mdb.h"

#define KeyMax 5

static void die(const char *message)
{
    perror(message);
    exit(1); 
}

int main(int argc, char **argv)
{
    /*
     * open the database file specified in the command line
     */

    if (argc != 2) {
        fprintf(stderr, "%s\n", "usage: mdb-lookup <database_file>");
        exit(1);
    }

    char *filename = argv[1];
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) 
        die(filename);

    /*
     * read all records into memory
     */

    struct List list;
    initList(&list);

    int loaded = loadmdb(fp, &list);
    if (loaded < 0)
        die("loadmdb");
    
    fclose(fp);

    /*
     * lookup loop
     */

    char line[1000];
    char key[KeyMax + 1];

    printf("lookup: ");
    fflush(stdout);
    while (fgets(line, sizeof(line), stdin) != NULL) {

        // must null-terminate the string manually after strncpy().
        strncpy(key, line, sizeof(key) - 1);
        key[sizeof(key) - 1] = '\0';

        // if newline is there, remove it.
        size_t last = strlen(key) - 1;
        if (key[last] == '\n')
            key[last] = '\0';

        // traverse the list, printing out the matching records
        struct Node *node = list.head;
        int recNo = 1;
        while (node) {
            struct MdbRec *rec = (struct MdbRec *)node->data;
            if (strstr(rec->name, key) || strstr(rec->msg, key)) {
                printf("%4d: {%s} said {%s}\n", recNo, rec->name, rec->msg);
            }
            node = node->next;
            recNo++;
        }

        printf("\nlookup: ");
        fflush(stdout);
    }

    // see if fgets() produced error
    if (ferror(stdin)) 
        die("stdin");

    /*
     * clean up and quit
     */

    freemdb(&list);
    return 0;
}
