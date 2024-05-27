#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include "mem_utils.h"

void write_transaction(char* file_name, mem_transaction t){
    FILE* file = fopen(file_name, "a");
    fprintf(file, "%lu %u %u %u\n", t.epoch_time, t.addr, t.prev, t.next);
    // Close the file
    fclose(file);
}


mem_transaction* read_transaction(mem_transaction* buffer, char* line){
    //TODO currently do not check for invalid inputs
    buffer->epoch_time = strtoul(strtok(line, " "), NULL, 10);
    buffer->addr = (uint32_t)strtoul(strtok(NULL," "), NULL, 10);
    buffer->prev = (uint32_t)strtoul(strtok(NULL," "), NULL, 10);
    buffer->next = (uint32_t)strtoul(strtok(NULL," "), NULL, 10);
    return buffer;
}

