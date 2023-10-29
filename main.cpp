#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main() {
    NODE* my_list = nullptr;

    my_list = (NODE*)calloc(START_LENGTH_OF_LIST, sizeof(NODE));

    list_init(my_list);
    int head = 0;
    int tail = 0;
    int free_head = 1;

    
    list_insert(my_list, 4, 5, &head, &tail, &free_head);
    LIST_DUMP(my_list,  head, tail, free_head, START_LENGTH_OF_LIST);
    list_insert(my_list, 4, 6, &head, &tail, &free_head);
    LIST_DUMP(my_list,  head, tail, free_head, START_LENGTH_OF_LIST);
    list_insert(my_list, 4, 7, &head, &tail, &free_head);
    LIST_DUMP(my_list,  head, tail, free_head, START_LENGTH_OF_LIST);

    
    list_dtor(my_list);
    free(my_list);

}