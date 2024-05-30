#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

const uint32_t HASH_TABLE_SIZE= 10;

struct hash_node {
    struct hash_node* next;
    uint64_t key;
    uint32_t val; 
};
typedef struct hash_node hash_node;

hash_node** make_table(){
    hash_node** hash_table = malloc(HASH_TABLE_SIZE* sizeof(hash_node*));
    for (uint32_t i = 0; i < HASH_TABLE_SIZE; i++){
        hash_table[i] = NULL;
    }
    return hash_table;
}


int hash(uint64_t key){
    return key % HASH_TABLE_SIZE;
}

hash_node* get_node(hash_node** hash_table, uint64_t key){
    hash_node* node = hash_table[hash(key)];
    
    if (node == NULL) return NULL;
    if (node->key == key){
        return node;
    }else{
        while(node->next != NULL){
            node = node->next;
            if (node->key == key) return node;
        }
        return NULL;
    }
}

uint32_t get_val(hash_node** hash_table, uint32_t key, int* error_status){
    *error_status = 1; 
    hash_node* node = get_node(hash_table, key);
    if (node == NULL) return 0;
    *error_status = 0;
    return node->val;
}

int set_val(hash_node** hash_table, uint32_t key, uint32_t val, int* error_status){
    *error_status = 1;
    //replacing value in existing node
    hash_node* new_node = get_node(hash_table, key);
    if (get_node(hash_table, key) != NULL){
        new_node->val = val;
        *error_status = 0;
        return hash(key);
    }
    //malloc new node
    new_node = malloc(sizeof(hash_node));
    if (new_node == NULL) return -1; // malloc fail
    new_node->key = key;
    new_node->val = val;
    //node is the pointer within the table itself...
    //it points to the first element of the linkedlist
    if (hash_table[hash(key)] == NULL) {
        // empty linked list
        hash_table[hash(key)] = new_node;
        hash_table[hash(key)]->next = NULL;
    }else{
        // shift list over
        new_node->next = hash_table[hash(key)];
        hash_table[hash(key)] = new_node;
    }
    *error_status = 0;
    return hash(key);
}

void print_node(hash_node* node){
    printf("%p, %lu, %u, %p\n", node, node->key, node->val, node->next);
}

uint32_t remove_key(hash_node** hash_table, uint64_t key, int* error_status){
    *error_status = 1;
    hash_node* to_remove = get_node(hash_table, key);
    // not actually present
    if (to_remove == NULL) return -1;
    hash_node** index_loc = &hash_table[hash(key)];
    if ((*index_loc)->key == key){
        *index_loc = (*index_loc)->next;
    }else{
        hash_node* prev = *index_loc;
        hash_node* node = (*index_loc)->next;
        while(node != NULL){
            if (node->key == key){
                prev->next = node->next;
            }
            prev = prev->next;
            node = node->next;
        }
    }
    uint32_t val = to_remove->val;
    free(to_remove);
    *error_status = 0;
    return val;
}

void print_hash_table(hash_node** hash_table){
    printf("[\n");
    for (uint32_t i = 0; i < HASH_TABLE_SIZE; i++){
        hash_node* node = hash_table[i];
        printf("%d: ", i);
        while(node != NULL){
            printf("(%lu, %u)->", node->key, node->val);
            node = node->next;
        }
        printf("\n");
    }
    printf("]\n");
}


