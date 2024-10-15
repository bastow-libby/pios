#include "list.h"
#include <stddef.h>
#include "rprintf.h"
#include "serial.h"
#include "mmu.h"
#include "page.h"
unsigned long get_timer_count(){
        unsigned long *timer_count_register = 0x3f003004;
        return *timer_count_register;
}
int getEL() {
    unsigned int el;
    asm("mrs %0,CurrentEL"
       : "=r"(el)
       :
       :);
    return el>>2;
}


char glbl[128];

void kernel_main() {
    mapPages(0x0000, 0x0000);
    //Call load page table

    esp_printf(putc, "Current Execution Level is %d\r\n", getEL());
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
