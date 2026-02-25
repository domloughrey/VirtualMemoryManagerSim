#ifndef TASK4_H
#define TASK4_H

#define PAGE_SIZE 4096        
#define NUM_PAGES 1024         
#define NUM_FRAMES 256   

#define TLB_SIZE 32

#include "vm_structs.h"
#include "tlb.h"
#include "queue.h"

void runTask4(const char *filename);

#endif