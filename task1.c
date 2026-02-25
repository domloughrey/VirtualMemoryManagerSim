#include <stdio.h>
#include <stdlib.h>
#include "task1.h"

void runTask1(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    unsigned int logical_address;
    while (fscanf(file, "%u", &logical_address) == 1) {
        // mask the logical address
        unsigned int masked = logical_address & 0x3FFFFF;   // rightmost 22 bits

        // extract page number and offset
        unsigned int page_number = masked >> 12;    // top 10 bits of masked
        unsigned int offset = masked & 0xFFF;       // bottom 12 bits of masked

        printf("logical-address=%u,page-number=%u,offset=%u\n",
               logical_address, page_number, offset);
    }

    fclose(file);
}