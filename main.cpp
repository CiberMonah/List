#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "list_dump.h"

int main() {
    NODE* my_list = nullptr;

    FILE* dot_file = nullptr;

    if ((dot_file = fopen("my_dot.dot", "w")) == NULL) {
        printf("File creating error");
        return 1;
    }

    my_list = (NODE*)calloc(START_LENGTH_OF_LIST, sizeof(NODE));

    list_init(my_list);

    int head = 0;
    int tail = 0;
    int free_head = 1;
                                                               
    list_insert(my_list, 4, 5, &head, &tail, &free_head);               
    list_insert(my_list, 4, 6, &head, &tail, &free_head);
    list_insert(my_list, 4, 7, &head, &tail, &free_head);

    //int* search_array = list_find(my_list, head, 5);

    // for(int i = 0; i < search_array[0]; i++) {
    //     printf("%d ", search_array[i]);
    // }

    //make_dot_dump(dot_file, my_list, head, tail, free_head, START_LENGTH_OF_LIST);

    LIST_HTML_DUMP(my_list, head, tail, free_head, START_LENGTH_OF_LIST);

    list_dtor(my_list);

    fclose(dot_file);
    //free(search_array);
    free(my_list);

}