#include <stdio.h>
#include <stdlib.h>
#include "task3.h"

void runTask3(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    PageTableEntry page_table[NUM_PAGES] = {0};  
    int next_free_frame = 0;
    FIFOQueue fifo_queue;
    initQueue(&fifo_queue);     // initalize FIFO queue

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
            frame_number = page_table[page_number].frame_number;
        } else {
            page_fault = 1;

            if (next_free_frame < NUM_FRAMES) {
                frame_number = next_free_frame++;   // Use next free frame
            } else {
                int evicted_page = dequeue(&fifo_queue);    // Evict oldest page (FIFO)
                frame_number = page_table[evicted_page].frame_number;
                page_table[evicted_page].present = 0;
                printf("evicted-page=%d,freed-frame=%d\n", evicted_page, frame_number);
            }

            // map new page
            page_table[page_number].present = 1;
            page_table[page_number].frame_number = frame_number;
            
            // track the page in the FIFO queue
            enqueue(&fifo_queue, page_number);
        }

        unsigned int physical_address = frame_number * PAGE_SIZE + offset;

        printf("page-number=%u,page-fault=%d,frame-number=%d,physical-address=%u\n",
               page_number, page_fault, frame_number, physical_address);
    }
    fclose(file);
}