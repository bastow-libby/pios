#include "list.h"
#include "delay.h"
#include <stddef.h>
unsigned long get_timer_count(){
        unsigned long *timer_count_register = 0x3f003004;
        return *timer_count_register;
}


char glbl[128];

void kernel_main() {
    unsigned long time = get_timer_count();
    milisec_delay();
    struct list_element *c = {NULL, 0};
    struct list_element *b = {&c, 0};
    struct list_element *a = {&b, 0};
    struct list_element *head = &a;
    list_add(head, a);
    list_add(head, b);
    list_add(head, c);
    list_remove(head, c);

    //initialize variables, bring in external variables
    char *bssstart, *bssend;
    extern char __bss_start, __bss_end;
    //set variables equal to values found in linkerscript
    bssstart = &__bss_start;
    bssend = &__bss_end;
    //edit for testing 

    //loop to iterate through bss, setting each value to zero
    char *i;
    for (i = bssstart; i < bssend; i++) {
   	*i = 0;	
    }
    while(1){
    }
}
