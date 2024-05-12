#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "mem_utils.h"

int write_transaction(char* file_name, uint32_t addr, uint32_t prev, uint32_t new){
    FILE* file = fopen(file_name, "a");
    time_t current_time = time(NULL);
    fprintf(file, "%lu %u %u %u\n", current_time, 1, 0, 3);
    // Close the file
    fclose(file);
}



int main(void* args){
    FILE *file;
    char buffer[100]; // Buffer to store the read data

    // Open the file for reading
    file = fopen("example.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read data from the file using fgets
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        // Do something with the data, for example, print it
        printf("%s", buffer);
    }

    // Close the file
    fclose(file);

    
    char *fileName = "output.txt";
    write_transaction(fileName, 1, 0, 2);

    return 0;
}