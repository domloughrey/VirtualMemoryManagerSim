#include "tlb.h"
#include <stdio.h>

// initializes all TLB entries as invalid and resets global time
void initTLB(TLB *tlb) {
    for (int i = 0; i < TLB_SIZE; i++) {
        tlb->entries[i].valid = 0;
    }
    tlb->time = 0;
}

// searches TLB for a page
int tlbLookup(TLB *tlb, int page_number, int *frame_number) {
    tlb->time++; // advance global time
    for (int i = 0; i < TLB_SIZE; i++) {
        if (tlb->entries[i].valid && tlb->entries[i].page_number == page_number) {
            *frame_number = tlb->entries[i].frame_number;
            tlb->entries[i].last_used = tlb->time;
            return 1; // hit
        }
    }
    return 0; // miss
}

// updates the TLB using LRU replacement
void updateTLB(TLB *tlb, int page_number, int frame_number) {
    tlb->time++;
    int lru_index = -1;
    unsigned long min_time = (unsigned long)-1;

    for (int i = 0; i < TLB_SIZE; i++) {
        if (!tlb->entries[i].valid) {
            lru_index = i;
            break;
        } else if (tlb->entries[i].last_used < min_time) {
            min_time = tlb->entries[i].last_used;
            lru_index = i;
        }
    }

    int replaced_page = tlb->entries[lru_index].valid ? tlb->entries[lru_index].page_number : -1;

    tlb->entries[lru_index].page_number = page_number;
    tlb->entries[lru_index].frame_number = frame_number;
    tlb->entries[lru_index].last_used = tlb->time;
    tlb->entries[lru_index].valid = 1;

    if (replaced_page == -1) {
        printf("tlb-remove=none,tlb-add=%d\n", page_number);
    } else {
        printf("tlb-remove=%d,tlb-add=%d\n", replaced_page, page_number);
    }
}

// invalidates a TLB entry by page number and returns new TLB size
int flushTLBEntry(TLB *tlb, int page_number) {
    int new_size = 0;
    for (int i = 0; i < TLB_SIZE; i++) {
        if (tlb->entries[i].valid) {
            if (tlb->entries[i].page_number == page_number) {
                tlb->entries[i].valid = 0;
                continue;
            }
            new_size++;
        }
    }
    return new_size;
}