#ifndef LIST_DUMP_H_INCLUDED
#define LIST_H_INCLUDED

#define LIST_DUMP(file, dotf, list, h, t, f, size) ({                                                    \
    dump_list((file), (dotf) (list), h, t, f, size, __FILE__, __PRETTY_FUNCTION__, __LINE__);             \
    })

void dump_list(FILE* dump_file, FILE* dot_file, NODE* list, int head, int tail, int free_head, unsigned int list_size, const char* file, const char* func, const int line);
void make_dot(FILE* dot_file, NODE* list, int head, int tail, int free_head, unsigned int list_size);

#endif