#include "list.h"
#include <stddef.h>
#include "rprintf.h"
#include "serial.h"
#include "mmu.h"
#include "page.h"
#include "sd.h"
#include "fat.h"
// Boot sector data struct. Put this either above main() or in its own header file.
/*
struct boot_sector {
char code[3];
char oem_name[8];
uint16_t bytes_per_sector;
uint8_t num_sectors_per_cluster;
uint16_t num_reserved_sectors;
uint8_t num_fat_tables;
uint16_t num_root_dir_entries;
uint16_t total_sectors;
uint8_t media_descriptor;
uint16_t num_sectors_per_fat;
uint16_t num_sectors_per_track;
uint16_t num_heads;
uint32_t num_hidden_sectors;
uint32_t total_sectors_in_fs;
uint8_t logical_drive_num;
uint8_t reserved;
uint8_t extended_signature;
uint32_t serial_number;
char volume_label[11];
char fs_type[8];
char boot_code[448];
uint16_t boot_signature;
}__attribute__((packed));
*/
extern struct table_descriptor_stage1 L1table[512] __attribute__((aligned(4096)));
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
    char arr[] ="TESTFILE.TXT";
    fatOpen(arr);
	
    // mapPages(0x0000, 0x0000);
    //Call load page table
    mapPages(0x0000, 0x0000);
    loadPageTable(&L1table[0]);

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
