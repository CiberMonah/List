#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "list_dump.h"

int main() {
    NODE* my_list = nullptr;

    my_list = (NODE*)calloc(START_LENGTH_OF_LIST, sizeof(NODE));

    int list_size = START_LENGTH_OF_LIST;

    list_init(my_list);

    int head = 0;
    int tail = 0;
    int free_head = 1;

    LIST_HTML_DUMP(my_list, head, tail, free_head, list_size);
                                                               
    list_insert(my_list, 4, 5, &head, &tail, &free_head); 

    LIST_HTML_DUMP(my_list, head, tail, free_head, list_size);

    int insert_id =list_insert(my_list, 4, 6, &head, &tail, &free_head);
    
    LIST_HTML_DUMP(my_list, head, tail, free_head, list_size);

    list_delete(my_list, insert_id, &head, &tail, &free_head);

    LIST_HTML_DUMP(my_list, head, tail, free_head, list_size);

    list_insert(my_list, 4, 7, &head, &tail, &free_head);

    LIST_HTML_DUMP(my_list, head, tail, free_head, list_size);

    realloc_list(&my_list, &list_size, 25, &head, &tail, &free_head);                      //gets pointer on my_list, because pointer of my_list will change

    LIST_HTML_DUMP(my_list, head, tail, free_head, list_size);

    realloc_list(&my_list, &list_size, 3, &head, &tail, &free_head);

    LIST_HTML_DUMP(my_list, head, tail, free_head, list_size); 

    list_dtor(my_list);

    free(my_list);
}