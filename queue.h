#ifndef QUEUE_H
#define QUEUE_H

#include "vm_structs.h"

void initQueue(FIFOQueue* q);
void enqueue(FIFOQueue* q, int page_number);
int dequeue(FIFOQueue* q);

#endif