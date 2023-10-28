#include "list.h"
#include "stdlib.h"
#include "stdio.h"

void dump_list(NODE* list, unsigned int list_size, const char* file, const char* func, const int line) {

    const int NUMBER_OF_SPACES = 5;

    printf( "\nDUMP called in file: %s\n"
            "In function: %s\n"
            "On line: %d\n", file, func, line);

    printf("\nid:  ");
    for(unsigned int i = 0; i < list_size; i ++) {
        printf("%*d", NUMBER_OF_SPACES, i);
    } printf("\n\n");

    printf("data:");
    for(unsigned int i = 0; i < list_size; i ++) {
        if(list[i].data == FREE_DATA) 
            printf("%*s", NUMBER_OF_SPACES, "FREE");
        else if(list[i].data == POISON) 
            printf("%*s", NUMBER_OF_SPACES, "POIS");
        else 
            printf("%*d", NUMBER_OF_SPACES, list[i].data);
    } printf("\n\n");

    printf("next:");
    for(unsigned int i = 0; i < list_size; i ++) {
        printf("%*d", NUMBER_OF_SPACES, list[i].next_id);
    } printf("\n\n");

    printf("prev:");
    for(unsigned int i = 0; i < list_size; i ++) {
        printf("%*d", NUMBER_OF_SPACES, list[i].prev_id);
    } printf("\n\n");
}


void list_init(NODE* list) {
    list[0].data = POISON;
    list[0].next_id = -1;
    list[0].prev_id = -1;

    for(int i = 1; i < START_LENGTH_OF_LIST; i++) {
        list[i].data = FREE_DATA;

        if(i == START_LENGTH_OF_LIST - 1) {         //Important not to make id out of list
            list[i].next_id = 0;
        } else {
            list[i].next_id = i + 1;
        }

        list[i].prev_id = -1;
    }
}

void list_dtor(NODE* list) {
    for(int i = 1; i < START_LENGTH_OF_LIST; i++) {
        list[i].data = POISON;
        list[i].next_id = POISON;
        list[i].prev_id = POISON;
    }
}

