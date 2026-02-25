#include "queue.h"

void initQueue(FIFOQueue* q) {
    q->front = 0;
    q->rear = 0;
    q->size = 0;
}

void enqueue(FIFOQueue* q, int page_number) {
    if (q->size < NUM_FRAMES) {
        q->pages[q->rear] = page_number;
        q->rear = (q->rear + 1) % NUM_FRAMES;
        q->size++;
    }
}

int dequeue(FIFOQueue* q) {
    int page = q->pages[q->front];
    q->front = (q->front + 1) % NUM_FRAMES;
    q->size--;
    return page;
}