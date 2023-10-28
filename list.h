#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#define LIST_DUMP(list, size) ({                                                  \
    dump_list((list), size, __FILE__, __PRETTY_FUNCTION__, __LINE__);         \
    })


const int START_LENGTH_OF_LIST = 20;

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
void dump_list(NODE* list, unsigned int list_size, const char* file, const char* func, const int line);



#endif