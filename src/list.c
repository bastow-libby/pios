#include "list.h"
#include <stddef.h>

struct list_element c = {NULL, 0};
struct list_element b = {&c, 0};
struct list_element a = {&b, 0};
struct list_element *head = &a;


//write the list_add() function that adds elements to a linked list
void list_add(struct list_element **list_head, struct list_element *new_element){
	new_element->next = (struct list_element*)list_head; //new element's next becomes the 
					     //same as the head's next (null)
	*list_head = new_element; //head now points to new_element
}


//write the list_remove() function that removes elements from a linked list
void list_remove(struct list_element *list_head, struct list_element *element){
	struct list_element *current = list_head;
	while (current->next != NULL && current->next != element) {
		current = current->next;
	}
	current->next = element->next;
}
