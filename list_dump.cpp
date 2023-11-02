#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "list_dump.h"

static void print_list_chain(FILE* dot_file, NODE* list, int start_id, const char* color) {
    while(list[start_id].data != POISON) {  
        fprintf(dot_file, "node%d: <next> -> node%d [color = \"%s\"];\n", start_id, list[start_id].next_id, color);
        if(list[start_id].prev_id != -1)
            fprintf(dot_file, "node%d: <prev> -> node%d [color = \"#006666\"];\n", start_id, list[start_id].prev_id);
        
        start_id = list[start_id].next_id;
    }
}

static void make_nodes_in_raw (FILE* dot_file, unsigned int list_size) {
    for(unsigned int i = 0; i < list_size; i++) {
        if(i == list_size - 1)
            fprintf(dot_file, "node%d", i);
        else
            fprintf(dot_file, "node%d ->", i);
    }
    fprintf(dot_file, "[weight = 10000; style = invis];\n");
}

static void print_node(FILE* dot_file, NODE* list, int id) {
    if(list[id].data == FREE_DATA) 
        fprintf(dot_file, "node%d[shape = Mrecord, style = filled, fillcolor=\"#DDFFDD\", label = \"NODE_%d| {<data> data : %s| <next> next : %d | <prev> prev : %d}\"];\n", id, id,"FREE", list[id].next_id, list[id].prev_id);
    else if(list[id].data == POISON) 
        fprintf(dot_file, "node%d[shape = Mrecord, style = filled, fillcolor=\"#FF0000\", label = \"NODE_%d| {<data> data : %s| <next> next : %d | <prev> prev : %d}\"];\n", id, id, "POIS", list[id].next_id, list[id].prev_id);
    else 
        fprintf(dot_file, "node%d[shape = Mrecord, style = filled, fillcolor=\"#FFAA55\", label = \"NODE_%d| {<data> data : %d| <next> next : %d | <prev> prev : %d}\"];\n", id, id, list[id].data, list[id].next_id, list[id].prev_id);
}

static void print_all_nodes (FILE* dot_file, NODE* list, unsigned int list_size) {
    fprintf(dot_file, "{rank = same;");

    for(unsigned int i = 0; i < list_size; i++) {
        print_node(dot_file, list, i);
    }

    fprintf(dot_file, "}\n");
}

static void print_main_cells(FILE* dot_file, int head, int tail, int free) {
    fprintf(dot_file, "head -> node%d [color = \"green\"];\n", head);
    fprintf(dot_file, "tail -> node%d [color = \"blue\"];\n", tail);
    fprintf(dot_file, "free -> node%d [color = \"red\"];\n", free);
}

void make_dot_dump(FILE* dot_file, NODE* list, int head, int tail, int free_head, unsigned int list_size) {

    fprintf(dot_file, "digraph G{"                          //set base settings and style
                            "graph [dpi = 150];"
                            "ranksep = 0.5;"
                            "splines = ortho;"
                            "edge[minlen = 3, penwidth = 3];"
                            "graph [bgcolor=\"#31353b\"]"
	                        "node[color=\"black\",fontsize=14];"
	                        "edge[color=\"darkgreen\",fontcolor=\"blue\",fontsize=12];"
                            "node[shape = record, style = rounded,fixedsize = true, height = 1, width = 3,fontsize = 20];\n");

    fprintf(dot_file,       "{rank = min;\n"                  //set sizes of cells head tail free
		                        "head[label = \"head\", shape = Mrecord, style = filled, fillcolor=\"#007700\",width = 1];\n"
	                        "}\n"
                            "{rank = min;\n"
                                "tail[label = \"tail\", shape = Mrecord, style = filled, fillcolor=\"#FF00FF\", width = 1];\n"
                            "}\n"
                            "{rank = min;\n"
                                "free[label = \"free\", shape = Mrecord, style = filled, fillcolor=\"#FFDDFF\", width = 1];\n"
                            "}\n");

    print_all_nodes(dot_file, list, list_size);

    print_main_cells(dot_file, head, tail, free_head);

    make_nodes_in_raw(dot_file, list_size);

    print_list_chain(dot_file, list, head, "#76EE00");                  //make data edges

    print_list_chain(dot_file, list, free_head, "#00C5CD");              //make free edges

    fprintf(dot_file, "}");

}

void make_html_dump(NODE* list, int head, int tail, int free_head, unsigned int list_size, const char* file, const char* func, const int line) {

    FILE* file_dot = nullptr;

    if ((file_dot = fopen("my_dot.dot", "w")) == NULL) {
        printf("File creating error");
        return;
    }

    make_dot_dump(file_dot, list, head, tail, free_head, list_size);

    fclose(file_dot);                                   //dot file created

    system("dot my_dot.dot -T png -o my_dot.png");      //png created
////////////////////////////////////////////////////////////////////////////////////////
    FILE* dump_txt = nullptr;

    if ((dump_txt = fopen("dump.txt", "w")) == NULL) {
        printf("File creating error");
        return;
    }

    dump_list(dump_txt, list, head, tail, free_head, list_size, file, func, line);
////////////////////////////////////////////////////////////////////////////////////////
    FILE* dump_html = nullptr;

    if ((dump_html = fopen("dump.html", "w")) == NULL) {
        printf("File creating error");
        return;
    }

    fprintf(dump_html, "<!DOCTYPE html>\n"
                       "<html>\n");
    fprintf(dump_html, "<iframe src=\"dump.txt\" width=\"100%%\" height=\"300\">\n");
    fprintf(dump_html, "</iframe>\n");

    fprintf(dump_html, "<img src=\"my_dot.png\">\n");   //Added img
    fprintf(dump_html, "</html>\n");


    fclose(dump_html);
}

void dump_list(FILE* dump_file, NODE* list, int head, int tail, int free_head, unsigned int list_size, const char* file, const char* func, const int line) {

    const int NUMBER_OF_SPACES = 5;

    fprintf(dump_file, "\nDUMP called in file: %s\n"
            "In function: %s\n"
            "On line: %d\n", file, func, line);

    fprintf(dump_file,"\nList head: %d\n", head);
    fprintf(dump_file,"List tail: %d\n", tail);
    fprintf(dump_file,"free list head: %d\n", free_head);

    fprintf(dump_file,"\nid:  ");
    for(unsigned int i = 0; i < list_size; i ++) {
        fprintf(dump_file, "%*d", NUMBER_OF_SPACES, i);
    } fprintf(dump_file, "\n\n");

    fprintf(dump_file, "data:");
    for(unsigned int i = 0; i < list_size; i ++) {
        if(list[i].data == FREE_DATA) 
            fprintf(dump_file, "%*s", NUMBER_OF_SPACES, "FREE");
        else if(list[i].data == POISON) 
            fprintf(dump_file, "%*s", NUMBER_OF_SPACES, "POIS");
        else 
            fprintf(dump_file, "%*d", NUMBER_OF_SPACES, list[i].data);
    } fprintf(dump_file, "\n\n");

    fprintf(dump_file, "next:");
    
    for(unsigned int i = 0; i < list_size; i ++) {
        fprintf(dump_file, "%*d", NUMBER_OF_SPACES, list[i].next_id);
    } fprintf(dump_file, "\n\n");

    fprintf(dump_file, "prev:");

    for(unsigned int i = 0; i < list_size; i ++) {
        fprintf(dump_file, "%*d", NUMBER_OF_SPACES, list[i].prev_id);
    } fprintf(dump_file, "\n\n");
}