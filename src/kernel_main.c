
unsigned long get_timer_count(){
        unsigned long *timer_count_register = 0x3f003004;
        return *timer_count_register;
}

char glbl[128];

void kernel_main() {
    unsigned long *time = get_timer_count();
    

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
