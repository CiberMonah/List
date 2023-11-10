# List
Here is an implementation of a doubly linked list in an array. This implementation allows you to access any of the list items to insert/delete at the same time.
![image](https://github.com/CiberMonah/List/assets/142305833/ba35c3fd-2539-4aaf-8cbf-f70e798d76bc)

# DUMP

I used graphviz  https://graphviz.org/ to make images of list

type this in console to make inage from dot file

** dot my_dot*.dot -T png -o my_dot*.png **

My dump generates images and put them to one html file for convenient debugging

![image](https://github.com/CiberMonah/List/assets/142305833/1a62a9c6-d0fe-4890-ae35-59cef0526dee)

# Functions

There are realisations of 4 functions:
1. Insert
2. Delete
3. Find_elem
4. Realloc_list

## Realloc
List at start:
![image](https://github.com/CiberMonah/List/assets/142305833/eb95f45c-5bb6-43c3-9adf-4385b3a4beee)
### Reallocation on biiger size
![image](https://github.com/CiberMonah/List/assets/142305833/c72d4fb1-5e75-46de-97b5-98f627ba87c9)
### Reallocation on less size
![image](https://github.com/CiberMonah/List/assets/142305833/a6b1f26c-9434-4189-ba0d-c602d1c1192c)

## Insertion
While insertion function finds free element and put data in it, and puts next_id and prev_id according the place we insert

List before insertion element

![image](https://github.com/CiberMonah/List/assets/142305833/4f6927c8-af43-440a-8d36-1a3be8b82e1c)

Than use function:

list_insert(my_list, 4, 6, &head, &tail, &free_head);

And our list looks:

![image](https://github.com/CiberMonah/List/assets/142305833/266288ea-46eb-440d-9f83-e74ed3520c98)

Then:

list_insert(my_list, 4, 7, &head, &tail, &free_head);

![image](https://github.com/CiberMonah/List/assets/142305833/56ba7783-385a-41f3-9a35-15caafc71183)

## Delete node
When delete node put thi node to the free list, and make 2 neighbour points on each other

After insertion remember insertion id
*int insert_id = list_insert(my_list, 4, 7, &head, &tail, &free_head);*
**list_delete(my_list, insert_id, &head, &tail, &free_head);**
List before delete:
![image](https://github.com/CiberMonah/List/assets/142305833/baba560f-645b-4847-a930-73edfe72e297)

List after delete:
![image](https://github.com/CiberMonah/List/assets/142305833/74e950ab-234a-4211-99ae-1999c2197884)

