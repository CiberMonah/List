#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED


const int START_LENGTH_OF_LIST = 8;

typedef int Elem_t;

const Elem_t FREE_DATA = -404;
const Elem_t POISON = -505;


struct NODE {
    Elem_t data;
    int next_id;
    int prev_id;
};

void list_init(NODE* list);
void list_dtor(NODE* list);
void list_delete(NODE* list, int delete_id, int* head, int* tail, int* free_head);
void list_insert(NODE* list, int insert_id, Elem_t elem, int* head, int* tail, int* free_head);
int* list_find(NODE* list, int head_id, Elem_t elem);

#endif