#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include "hash_table.c"
#include "time.h"


int check_for_change(hash_node** hash_table, uint32_t* mem_block, uint32_t mem_block_size, uint32_t mem_block_start_index, mem_transaction* transaction_buffer){
    uint32_t index = 0;
    int error_status = 0;
    int count_changes = 0;
    for(index; index < mem_block_size; index++){
        assert(error_status == 0);
        if(mem_block[index] != 0 && mem_block[index] != get_val(hash_table, index, &error_status)){
            //change
	    transaction_buffer[count_changes].epoch_time = time(NULL);
	   transaction_buffer[count_changes].addr = mem_block_start_index + index;
	   transaction_buffer[count_changes].prev = get_val(hash_table, mem_block_start_index + index, &error_status);
            if (error_status == 1)transaction_buffer[count_changes].prev = 0;
	    transaction_buffer[count_changes].new = mem_block[index];
            count_changes++;
        }
    }
    return changes;
}

int main(void* args){
    //printf("helloworld\n");
    //alloc 4 gigs
    const int SIZE = 100000;
    void* mem_root = calloc(SIZE, sizeof(uint32_t));
    if (mem_root == NULL){
        printf("Alloc failed\n");
        return 2;
    }

    hash_node** hash_table = make_table();
    mem_transaction* recent_transactions[10];
    // begin testing
    void* mem = mem_root;
    uint32_t* mem_read = mem;
    *mem_read = 100000000;
    check_for_change(hash_table, mem_read, SIZE, 0, recent_transactions);
    printf("%lu, %u, %u, %u", recent_transaction[0].epoch_time, recent_transactions[0].addr, recent_transaction[0].prev, recent_transaction[0].new);
    free(mem_root);
}
