#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BLOCK_SIZE 4096
#define VDISK_FILE "virtual_disk.bin"

void write_block (int block_number, const void* data) {
    FILE* disk = fopen (VDISK_FILE, "r+b");
    if (!disk) {
        perror ("Failed to open virtual disk!");
        exit (1);
    }
    fseek (disk, block_number * BLOCK_SIZE, SEEK_SET);
    fwrite (data, 1, BLOCK_SIZE, disk);
    fclose (disk);
}

void read_block (int block_number, void* buffer) {
    FILE* disk = fopen (VDISK_FILE, "rb");
    if (!disk) {
        perror ("Failed to open virtual disk!");
        exit (1);
    }
    fseek (disk, block_number * BLOCK_SIZE, SEEK_SET);
    fread (buffer, 1, BLOCK_SIZE, disk);
    fclose (disk);
}

int main () {
    FILE* disk = fopen (VDISK_FILE, "wb");
    if (!disk) {
        perror ("Failed to create virtual disk!");
        return 1;
    }
    ftruncate (fileno (disk), 10 * 1024 * 1024);
    fclose (disk);
    char block[BLOCK_SIZE];
    memset (block, 0, BLOCK_SIZE);
    strcpy (block, "hello.");
    write_block (0, block);
    char readback[BLOCK_SIZE];
    read_block (0, readback);
    printf ("readback = %s\n", readback);
    return 0;
}
