#ifndef TASK3_H
#define TASK3_H

#define PAGE_SIZE 4096        
#define NUM_PAGES 1024         
#define NUM_FRAMES 256         

#include "vm_structs.h"
#include "queue.h"

void runTask3(const char *filename);

#endif