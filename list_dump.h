#ifndef LIST_DUMP_H_INCLUDED
#define LIST_H_INCLUDED

#define LIST_DUMP(file, list, h, t, f, size) ({                                                       \
    dump_list((file), (dotf) (list), h, t, f, size, __FILE__, __PRETTY_FUNCTION__, __LINE__);               \
    })

#define LIST_HTML_DUMP(list, h, t, f, size) ({                                                              \
    make_html_dump((list), h, t, f, size, __FILE__, __PRETTY_FUNCTION__, __LINE__);                         \
    })

void make_html_dump(NODE* list, int head, int tail, int free_head, unsigned int list_size, const char* file, const char* func, const int line);
void dump_list(FILE* dump_file, NODE* list, int head, int tail, int free_head, unsigned int list_size, const char* file, const char* func, const int line);
void make_dot_dump(FILE* dot_file, NODE* list, int head, int tail, int free_head, unsigned int list_size);

#endif