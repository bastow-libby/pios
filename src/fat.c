#include "sd.h" // See this file for function prototype of ata_lba_read()
struct boot_sector *bs;
char bootSector[512]; // Allocate a global array to store boot sector
char fat_table[8*512];
unsigned int root_sector;

int fatInit() {
    sd_readblock(0, bootSector, 1); // Read sector 0 from disk drive into bootSector array
    bs = bootSector; // Point boot_sector struct to the boot sector so we can read fields
    // Print out some of the elements of the BIOS information block using rprintf...
    // TODO: Validate the boot signature = 0xaa55
    // TODO: Validate fs_type = "FAT12" using strcmp
    // TODO: Read FAT table from the SD card into array fat_table
    // TODO: Compute root_sector as:
    // num_fat_tables + num_sectors_per_fat + num_reserved_sectors + num_hidden_sectors
    return 0;
}
int fatOpen() {
     return 0;
}
int fatRead() {
    return 0;
}
