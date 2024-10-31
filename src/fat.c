#include "fat.h"
#include "sd.h" // See this file for function prototype of ata_lba_read()
#include "rprintf.h"
#include "serial.h"
struct boot_sector *bs;
char bootSector[512]; // Allocate a global array to store boot sector
char fat_table[8*512];
char rde_region[2048];
char rde_entry[32];
unsigned int root_sector;

struct root_directory_entry* fatInit() {
    sd_init();
    sd_readblock(0, bootSector, 1); // Read sector 0 from disk drive into bootSector array
    bs = (struct boot_sector*)bootSector; // Point boot_sector struct to the boot sector so we can read   
    
    // Validate boot signature
    if (bs->boot_signature != 0xAA55) {
        esp_printf(putc, "Invalid boot signature: 0x%04X\n", bs->boot_signature);
        return -1; // Error code
    }
    esp_printf(putc, "fs type = %s\n", bs->fs_type);
    // Validate fs_type
    //if (my_strcmp(bs->fs_type, "FAT12") != 0) {
        //esp_printf(putc, "Invalid file system type: %s\n", bs->fs_type);
        //return -1; // Error code
   // }

    esp_printf(putc, "Boot signature(should be 0xaa55)  = %d\n", bs->extended_signature);
    esp_printf(putc, "fs_type(should be 'FAT12') = %s\n", bs->fs_type);
    
    // Read FAT table
    sd_readblock(512, fat_table, 8 * 512);

    // Compute root sector
    root_sector = (bs->num_fat_tables * bs->num_sectors_per_fat) + bs->num_reserved_sectors + bs->num_hidden_sectors;

    // Read root directory entries
    sd_readblock(root_sector, rde_region, 512); 
    struct root_directory_entry *rde = (struct root_directory_entry*)rde_region;
    //return to fatopen here
    return (struct root_directory_entry*)rde_region;
}

int fatOpen(char *target){
    struct root_directory_entry *rde = fatInit();
    // Print file names in root directory
    for(int j = 0; j < 16; j++) {
         // Prepare the filename
         char filename[12]; // 8 + 3 + 1 for null terminator
         int k = 0;  
          // Copy filename
         for (k = 0; k < 8; k++) {
             if (rde[j].file_name[k] == ' ') break; // Stop at space
             filename[k] = rde[j].file_name[k]; // Copy character
         }
         filename[k] = '.'; // Add the dot at 8 (after name)
         k++;
 
         // Copy extension
         for (int m = 0; m < 3; m++) {
             if (rde[j].file_extension[m] == ' ') break; // Stop at space
             filename[k++] = rde[j].file_extension[m]; // Copy character
         }
         filename[k] = '\0'; // Null-terminate the string
 
         // Use strcmp to see if file name matches the target, if so, return 0
         esp_printf(putc, "Name of file %d: \"%s\"\n", j, filename);
         if (my_strcmp(filename, target) == 0) {
                 esp_printf(putc, "File found %d\n", 1);
  		 
                 //read the root directory entry table struct to find data cluster and size
                 fatRead(rde[j].cluster, rde[j].file_size);
		 return 0;
         }
     }
     esp_printf(putc, "File not found %d\n", 1);
     return -1;
}

int fatRead(int cluster, int size) {
    esp_printf(putc, "Cluster number = %d\n", cluster);
    esp_printf(putc, "Size of file = %d\n", size);
    int sector_size = 512; 
    int cluster_size = bs->num_sectors_per_cluster;
    esp_printf(putc, "Reached line %d\n", 84);
    // Calculate the starting sector for the given cluster
    // Cluster numbers usually start from 2 (according to internet)
    int start_sector = ((cluster - 2) * cluster_size) + (bs->num_fat_tables * bs->num_sectors_per_fat) + bs->num_reserved_sectors + bs->num_hidden_sectors;

    esp_printf(putc, "start = %d\n", start_sector);
    if (cluster < 2) {
    	esp_printf(putc, "Invalid cluster number: %d\n", cluster);
    	return -1; // Error: Invalid cluster
    }
    char buf[cluster_size * sector_size];
    // Read data from the calculated starting sector into the buffer
    int result = sd_readblock(start_sector, buf, 1);
    
    esp_printf(putc, "Bytes read = %d\n", result);    
    for (int i = 0; i < size; i++) {
        esp_printf(putc, "buf[%d] = %c\n", i, buf[i]);
    }
    return 0;
}


int my_strcmp(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        // Compare the characters
        if (*s1 != *s2) {
            return 1; // Return 1 if strings do not match
        }
        s1++;
        s2++;
    }

    // Check if both strings ended at the same time
    if (*s1 == '\0' && *s2 == '\0') {
        return 0; // Strings match
    }

    return 1; // Strings do not match (one ended before the other)
}
