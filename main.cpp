#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main() {
    NODE* my_list = nullptr;

    my_list = (NODE*)calloc(START_LENGTH_OF_LIST, sizeof(NODE));

    list_init(my_list);
    LIST_DUMP(my_list, START_LENGTH_OF_LIST);
    list_dtor(my_list);

    free(my_list);
}