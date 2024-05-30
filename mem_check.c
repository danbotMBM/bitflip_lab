#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h> // For sleep function
#include "hash_table.c"
#include "time.h"
#include "record_transactions.c"

char* FILENAME = "transactions.txt";

int check_for_change(hash_node** hash_table, uint32_t* mem_block, uint32_t mem_block_size, uint32_t mem_block_start_index, mem_transaction* transaction_buffer){
    uint32_t index = 0;
    int error_status = 0;
    int count_changes = 0;
    for(index; index < mem_block_size; index++){
        assert(error_status == 0);
        if(mem_block[index] != get_val(hash_table, index, &error_status)){
            //change
            transaction_buffer[count_changes].epoch_time = time(NULL);
            transaction_buffer[count_changes].addr = mem_block_start_index + index;
            transaction_buffer[count_changes].prev = get_val(hash_table, mem_block_start_index + index, &error_status);
            if (error_status == 1)transaction_buffer[count_changes].prev = 0;
            transaction_buffer[count_changes].next = mem_block[index];
            error_status = 0;
            count_changes++;
        }
        error_status = 0;
    }
    return count_changes;
}

int setup_state(hash_node** hash_table, uint32_t* mem_root){
     // Open the file for reading
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    char buffer[100]; // Buffer to store the read data
    // Read data from the file using fgets
    int num_vals = 0;
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        int error = 0;
        // Do something with the data, for example, print it
        mem_transaction* tbuffer = malloc(sizeof(mem_transaction));
        read_transaction(tbuffer, buffer);
        printf("FOUND_IN_TRANSACTION_LIST: %lu, %u, %u, %u\n", tbuffer->epoch_time, tbuffer->addr, tbuffer->prev, tbuffer->next);
        int x = set_val(hash_table, tbuffer->addr, tbuffer->next, &error);
        mem_root[tbuffer->addr] = tbuffer->next;
        free(tbuffer);
        num_vals++;
    }
    return num_vals;
}

int main(void* args){
    //printf("helloworld\n");
    //alloc 400MB
    const uint32_t SIZE = 3500000000u;
    uint32_t* mem_root = calloc(SIZE, sizeof(uint32_t));
    if (mem_root == NULL){
        printf("Alloc failed\n");
        return 2;
    }

    hash_node** hash_table = make_table();
    mem_transaction* recent_transactions = calloc(100, sizeof(mem_transaction));;
    int num_vals = setup_state(hash_table, mem_root);
    printf("parsed %d transactions\n", num_vals);
    // begin testing
    uint32_t* mem_read = mem_root;    
    while(1){
        int error = 0;
        int num_changes = check_for_change(hash_table, mem_read, SIZE, 0, recent_transactions);
        printf("%d\n", num_changes);
        for (int i = 0; i < num_changes; i++){
            printf("Detected change: %lu, %u, %u, %u\n", recent_transactions[i].epoch_time, recent_transactions[i].addr, recent_transactions[i].prev, recent_transactions[i].next);
            set_val(hash_table, recent_transactions[i].addr, recent_transactions[i].next, &error);
            write_transaction(FILENAME, recent_transactions[i]);
        }
        sleep(60);
    }
    
    free(mem_root);
}
