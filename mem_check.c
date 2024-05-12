#include <stdio.h>
#include <stdlib.h>
#include "mem_utils.h"




int main(void* args){
    //printf("helloworld\n");
    //alloc 4 gigs
    const int SIZE = 100000;
    void* mem_root = calloc(SIZE, sizeof(uint32_t));
    if (mem_root == NULL){
        printf("Alloc failed\n");
        return 2;
    }
    void* mem = mem_root;
    uint32_t* mem_read = mem;
    *mem_read = 100000000;
    mem++;
    for (int i = 0; i < SIZE; i++){
        printf("%u\n", *mem_read);
        mem_read++;   
    }
    free(mem_root);
}