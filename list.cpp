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

int list_insert(NODE* list, int insert_id, Elem_t elem, int* head, int* tail, int* free_head) {
    if(*head == 0) {                                        //first insert
        *head = insert_id;
        *tail = insert_id;
        list[insert_id].data = elem;
        list[insert_id].next_id = 0;
        list[insert_id].prev_id = 0;

        if(insert_id != 1) {                              
            list[insert_id - 1].next_id = insert_id + 1;    
        }

        return insert_id;
    }

    if(insert_id == *head)
        *head = insert_id;

    if(insert_id == *tail)
        *tail = *free_head;

    int new_free_head = list[*free_head].next_id;

    //Elem_t old_data = list[insert_id].data;         //Changed data
    list[*free_head].data = elem;

    list[*free_head].prev_id = insert_id;
    list[list[insert_id].next_id].prev_id = *free_head;
    list[*free_head].next_id = list[insert_id].next_id;

    list[insert_id].next_id = *free_head;

    int tmp = *free_head;

    *free_head = new_free_head;

    return tmp;
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

//Do not use this function

void realloc_list (NODE** list, int* list_size, int new_list_size, int* head, int* tail, int* free_head) {
    if(new_list_size <= *list_size) {
        NODE* new_list = (NODE*)calloc(new_list_size, sizeof(NODE));       //Calloc list with smaller size (UNSAFE and very long)
        new_list[0].data = POISON;
        new_list[0].prev_id = -1;
        new_list[0].next_id = -1;

        int next = *head;

        *head = 1;
        
        int i = 1;

        while((*list + next)->data != POISON) {                                        //Copy all nodes to new_list starting from 1 element
            //printf("data %d, next %d\n", (*list + next)->data, (*list + next)->next_id);
            new_list[i].data = (*list + next)->data;
            new_list[i].prev_id = i - 1;

            if(i == new_list_size) {                                                //number of nodes >= list size; may loose information
                new_list[i].prev_id = i - 1;
                new_list[i].next_id = 0;
                
                *list = new_list;
                
                *free_head = 0;
                *tail = i - 1;
                *list_size = new_list_size;
                return;
            }
            new_list[i - 1].next_id = i;
            new_list[i].next_id = 0;

            i++;
            next = (*list + next)->next_id;
        }

        *tail = i - 1;
        *free_head = i;

        for(int j = i; j < new_list_size; j++) {                                     //set other nodes FREE
            new_list[j].data = FREE_DATA;
            new_list[j].prev_id = -1;
            if(j != new_list_size - 1)
                new_list[j].next_id = j + 1;
            else
                new_list[j].next_id = 0;
        }
        
        *list = new_list;
        *list_size = new_list_size;

    } else {                                                                        //Realloc to the biiger size
        *list = (NODE*)realloc(*list, new_list_size * sizeof(NODE));  
        if(*list == nullptr) {
            fprintf(stdin, "Memory realloc err");
            printf("I am not a programer\n");
            return;
        }
        int new_free_head = *list_size;
        
        (*list + *list_size)->prev_id = -1;
        (*list + *list_size)->next_id = *list_size + 1;
        (*list + *list_size)->data = FREE_DATA;

        for(int i = *list_size + 1; i < new_list_size - 1; i++) {
            (*list + i)->data = FREE_DATA;
            (*list + i)->prev_id = -1;
            (*list + i)->next_id = i + 1;                            
        }

        (*list + new_list_size - 1)->next_id = *free_head;                           //Add free nodes to the start of freelist
        (*list + new_list_size - 1)->prev_id = - 1;
        (*list + new_list_size - 1)->data = FREE_DATA;

        *free_head = new_free_head;
        *list_size = new_list_size;
    }
}
