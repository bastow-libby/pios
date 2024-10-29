#include "fat.h"
#include "sd.h" // See this file for function prototype of ata_lba_read()
#include "rprintf.h"
#include "serial.h"
struct boot_sector *bs;
char bootSector[512]; // Allocate a global array to store boot sector
char fat_table[8*512];
char rde_region[2048];
unsigned int root_sector;

int fatInit() {
    //struct boot_sector *bs = (struct boot_sector*)boot_sector;
    struct root_directory_entry *rde = (struct root_directory_entry*)rde_region;
    sd_init();
    sd_readblock(0, bootSector, 1); // Read sector 0 from disk drive into bootSector array
    bs = (struct boot_sector*)bootSector; // Point boot_sector struct to the boot sector so we can read fields  
    esp_printf(putc, "Boot signature(should be 0xaa55)  = %d\n", bs->extended_signature);
    esp_printf(putc, "fs_type(should be 'FAT12') = %s\n", bs->fs_type);
    
    //int strcmp (bs->fs_type, "FAT12");
  
    sd_readblock(512, fat_table, 8*512);
    
    int num_tables = bs->num_fat_tables;
    int sectors_per = bs->num_sectors_per_fat;
    int reserved = bs->num_reserved_sectors;
    int hidden = bs->num_hidden_sectors;
    root_sector = num_tables + sectors_per + reserved + hidden;
    for(int j = 0; j < 8; j++) {
                esp_printf(putc, "name of file %d: \"%s\"\n", j, rde[j].file_name); //file name is 8 char file name, . , 3
        }  //char extension

    // Print out some of the elements of the BIOS information block using rprintf...
    // TODO: Validate the boot signature = 0xaa55
    // TODO: Validate fs_type = "FAT12" using strcmp
    // TODO: Read FAT table from the SD card into array fat_table
    // TODO: Compute root_sector as:
    // num_fat_tables + num_sectors_per_fat + num_reserved_sectors + num_hidden_sectors
    //Itterate through rde until you find matching file????
    //Start at root_sector and then 
    return 0;
}
int fatOpen() {
    //
    //Read the boot sector for info abt disc geometry
  
       	return 0;
}
int fatRead() {

    return 0;
}
