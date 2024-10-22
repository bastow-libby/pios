#include "list.h"
#include "page.h"
#include <stddef.h>
struct ppage physical_page_array[128]; // 128 pages, each 2mb in length covers 256 megs of mem
struct list_element *head = NULL;
void init_pfa_list(void) {
//initialized a linked list of free pages
	
	for(int i = 0; i< 128; i++) {
		//struct list_element new = {NULL, NULL, &physical_page_array[i]}; 
		list_add(&head, &physical_page_array[i]);
		//physical page addresss at i equals the physcial page
		physical_page_array[i].physical_addr = 200000*i;
		
	}
//also need to initialize physical addr member of struc with address of the page

}

struct ppage *allocate_physical_pages(unsigned int npages) {
	//allocates one of more physical pages from the list of free pages
	struct list_element *target = {NULL, NULL, head->next};
	struct list_element *alloc_head = NULL;
	for(int i = 0; i < npages; i++) {
		list_remove(&head, &target);
		list_add(&alloc_head, target);
		target = target->next;
	}
	//unlink requested number of pages from the free link list and create a new seperate list
	//return a pointer to the new list
	return alloc_head;
}


void free_physical_pages(struct ppage *ppage_list){
	while (ppage_list->next != NULL) {
		list_add(&head, ppage_list->next);
		list_remove(ppage_list, ppage_list->next);
	//put them back in the list in order
        }
}

int page_main() {
	init_pfa_list();
	free_physical_pages(allocate_physical_pages(8));
	return 1;
}

