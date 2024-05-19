#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include "mem_utils.h"

int write_transaction(char* file_name, uint32_t addr, uint32_t prev, uint32_t new){
    FILE* file = fopen(file_name, "a");
    time_t current_time = time(NULL);
    fprintf(file, "%lu %u %u %u\n", current_time, 1, 0, 3);
    // Close the file
    fclose(file);
}


typedef struct mem_transaction mem_transaction;

mem_transaction* read_transaction(mem_transaction* buffer, char* line){
    //TODO currently do not check for invalid inputs
    buffer->epoch_time = strtoul(strtok(line, " "), NULL, 10);
    buffer->addr = (uint32_t)strtoul(strtok(NULL," "), NULL, 10);
    buffer->prev = (uint32_t)strtoul(strtok(NULL," "), NULL, 10);
    buffer->new = (uint32_t)strtoul(strtok(NULL," "), NULL, 10);
    return buffer;
}


int main(void* args){
    char *fileName = "transactions.txt";
    write_transaction(fileName, 1, 0, 2);
    FILE *file;
    char buffer[100]; // Buffer to store the read data

    // Open the file for reading
    file = fopen("transactions.txt", "r");njkl;h
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read data from the file using fgets
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        // Do something with the data, for example, print it
        mem_transaction* tbuffer = malloc(sizeof(mem_transaction));
        read_transaction(tbuffer, buffer);
        printf("%lu, %u, %u, %u\n", tbuffer->epoch_time, tbuffer->addr, tbuffer->prev, tbuffer->new);
        free(tbuffer);
    }

    // Close the file
    fclose(file);

    


    return 0;
}