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

    //   0    1    2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19                                                                  
    list_insert(my_list, 4, 5, &head, &tail, &free_head);               
    //POIS FREE FREE FREE    5 FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE
    list_insert(my_list, 4, 6, &head, &tail, &free_head);
    //POIS    6 FREE FREE    5 FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE
    list_insert(my_list, 4, 7, &head, &tail, &free_head);
    //POIS    6    7 FREE    5 FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE
    list_delete(my_list, 2, &head, &tail, &free_head);
    //POIS    6 FREE FREE    5 FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE

    int* search_array = list_find(my_list, head, 5);    //returns ptr on array {1, 1, 0 * 20 ...}

    for(int i = 0; i < search_array[0]; i++) {
        printf("%d ", search_array[i]);
    }

    list_dtor(my_list);

    free(search_array);
    free(my_list);

}