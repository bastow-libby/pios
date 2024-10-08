#ifndef LIST_H
#define LIST_H


//general purpose structure for a linked list
//
struct list_element {
	struct list_element *next;
	struct list_element *prev;
	int data;	
};

void list_add(struct list_element **list_head, struct list_element *new_element);void list_remove(struct list_element *list_head, struct list_element *element);


#endif 


