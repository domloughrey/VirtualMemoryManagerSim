#include <stdio.h>
#include <stdlib.h>
#include "task2.h"

#define PAGE_SIZE 4096        
#define NUM_PAGES 1024         
#define NUM_FRAMES 256         

typedef struct {
    int present;
    int frame_number;
} PageTableEntry;

void runTask2(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    PageTableEntry page_table[NUM_PAGES] = {0}; // initialize page table 
    int next_free_frame = 0;

    unsigned int logical_address;
    while (fscanf(file, "%u", &logical_address) == 1) {
        unsigned int masked = logical_address & 0x3FFFFF;   
        unsigned int page_number = masked >> 12;    
        unsigned int offset = masked & 0xFFF;       

        printf("logical-address=%u,page-number=%u,offset=%u\n",
               logical_address, page_number, offset);

        int page_fault = 0;
        int frame_number;

        if (page_table[page_number].present) {
            frame_number = page_table[page_number].frame_number; // page is already in memory
        } else {
            page_fault = 1;

            // assign next available frame
            frame_number = next_free_frame;
            page_table[page_number].present = 1;
            page_table[page_number].frame_number = frame_number;
            next_free_frame++;
        }

        unsigned int physical_address = frame_number * PAGE_SIZE + offset;

        printf("page-number=%u,page-fault=%d,frame-number=%d,physical-address=%u\n",
               page_number, page_fault, frame_number, physical_address);
    }
    fclose(file);
}