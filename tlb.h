#ifndef TLB_H
#define TLB_H

#include "vm_structs.h"

#define TLB_SIZE 32

typedef struct {
    int page_number;
    int frame_number;
    unsigned long last_used;
    int valid;
} TLBEntry;

typedef struct {
    TLBEntry entries[TLB_SIZE];
    unsigned long time;
} TLB;

// TLB Operations
void initTLB(TLB *tlb);
int tlbLookup(TLB *tlb, int page_number, int *frame_number);
void updateTLB(TLB *tlb, int page_number, int frame_number);
int flushTLBEntry(TLB *tlb, int page_number);

#endif