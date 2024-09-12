
struct list_element c = {NULL, 0};
struct list_element b = {&c, 0};
struct list_element a = {&b, 0};

//write the list_add() function that adds elements to a linked list
void list_add(struct list_element *list_head, struct list_element *new element){
	list_head->next = &new;
	return 0;
}


//write the list_remove() function that removes elements from a linked list
void list_remove(struct list_element *element){

	return 0;
}
