#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

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

int* list_find(NODE* list, int head_id, Elem_t elem) {
    //A lot of variants to find element in list
    //It depands of task
    //here realisation of searching by going on list chain
    int search_id = head_id;
    int* index_array = nullptr;      //index_array[0] - number of indexes with searching number

    index_array = (int*)calloc(START_LENGTH_OF_LIST, sizeof(int));
    
    if(index_array == NULL) {
        printf("Memory allocation error/n");
        assert(1);
    }

    int i = 1;

    while(list[search_id].data != POISON) {
        if(list[search_id].data == elem) {
            index_array[i++] = search_id;
            index_array[0]++;
        }
        search_id = list[search_id].next_id;
    }

    return index_array;
}
