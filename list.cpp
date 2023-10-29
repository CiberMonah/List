#include "list.h"
#include "stdlib.h"
#include "stdio.h"

static void print_list_chain(NODE* list, int start_id) {

    while(list[start_id].data != POISON) {
        if(list[start_id].data == FREE_DATA) 
            printf("%d - %s; ", start_id, "FREE");
        else    
            printf("%d - %d; ", start_id, list[start_id].data);
        
        start_id = list[start_id].next_id;
    }

    printf("\n");
}

void dump_list(NODE* list, int head, int tail, int free_head, unsigned int list_size, const char* file, const char* func, const int line) {

    const int NUMBER_OF_SPACES = 5;

    printf( "\nDUMP called in file: %s\n"
            "In function: %s\n"
            "On line: %d\n", file, func, line);

    printf("\nList head: %d\n", head);
    printf("List tail: %d\n", tail);
    printf("free list head: %d\n", free_head);

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

    printf("Data chain:\n");
    print_list_chain(list, head);
    printf("Free data chain\n");
    print_list_chain(list, free_head);
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

void list_insert(NODE* list, int insert_id, Elem_t elem, int* head, int* tail, int* free_head) {
    if(*head == 0) {            //first insert
        *head = insert_id;
        *tail = insert_id;
        list[insert_id].data = elem;
        list[insert_id].next_id = 0;
        list[insert_id].prev_id = 0;

        if(insert_id != 1) {                                //Это ROFLS
            list[insert_id - 1].next_id = insert_id + 1;    
        }

        return;
    }

    if(insert_id == *head)
        *head = insert_id;

    if(insert_id == *tail)
        *tail = *free_head;

    int tmp = list[insert_id].next_id;
    int new_free_head = list[*free_head].next_id;

    list[insert_id].next_id = *free_head;

    list[*free_head].prev_id = insert_id;
    list[*free_head].next_id = tmp;
    list[*free_head].data = elem;

    *free_head = new_free_head;
}


void list_delete(NODE* list, int delete_id, int* head, int* tail, int* free_head) {
    list[delete_id].data = FREE_DATA;
    *free_head = delete_id;

    if(delete_id == *head) {
        *head = list[delete_id].next_id;
    }
    if(delete_id == *tail) {
        *tail = list[delete_id].prev_id;
    }

    int prev = list[delete_id].prev_id;
    int next = list[delete_id].next_id;

    list[prev].next_id = next;
    list[next].prev_id = prev;
}


